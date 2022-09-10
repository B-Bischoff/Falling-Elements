#include "GridRenderer.h"

GridRenderer::~GridRenderer()
{
	delete [] _indices;
	delete [] _vertices;
}

GridRenderer::GridRenderer(const int& width, const int& height)
	: WIDTH(width), HEIGHT(height), _indices(nullptr), _vertices(nullptr)
{
	initializeMemory();
	generateIndices();
	initializeOpenglObjects();
	initializeVertexPositions();
}

void GridRenderer::initializeMemory()
{
	_indices = new uint32_t [WIDTH * HEIGHT * 6];
	if (_indices == nullptr)
	{
		std::cerr << "[GridRenderer] Initialization failed." << std::endl;
		std::cin.get();
		exit (1);
	}

	_vertices = new Vertex [WIDTH * HEIGHT * 4];
	if (_vertices == nullptr)
	{
		std::cerr << "[GridRenderer] Initialization failed." << std::endl;
		std::cin.get();
		exit (1);
	}
}

void GridRenderer::generateIndices()
{
	const int VERT_NB = WIDTH * HEIGHT * 6;

	int indiceOffset = 0;

	for (int i = 0; i < VERT_NB; i += 6)
	{
		// Triangle 1
		_indices[i] = indiceOffset;
		_indices[i + 1] = indiceOffset + 1;
		_indices[i + 2] = indiceOffset + 2;

		// Triangle 2
		_indices[i + 3] = indiceOffset + 2;
		_indices[i + 4] = indiceOffset + 3;
		_indices[i + 5] = indiceOffset;

		// DEBUG
		//std::cout << "tri1: " << indices[i] << " " << indices[i + 1] << " " << indices[i + 2];
		//std::cout << " tri2: " << indices[i + 3] << " " << indices[i + 4] << " " << indices[i + 5] << std::endl;

		indiceOffset += 4;
	}
}

void GridRenderer::initializeOpenglObjects()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * WIDTH * HEIGHT, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexArrayAttrib(_vbo, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexArrayAttrib(_vbo, 1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * WIDTH * HEIGHT * 6, _indices, GL_STATIC_DRAW);
}

void GridRenderer::initializeVertexPositions()
{
	const int CELL_SIZE = 2;
	const glm::vec3 defaultColor = glm::vec3(0.2f, 0.0f, 0.2f);
	
	//std::cout << "--------------------------" << std::endl;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int vertexNb = y * WIDTH + x;

			Vertex v1 = {
				glm::vec3((float)(CELL_SIZE * x), (float)(CELL_SIZE * y), 0.0f),
				defaultColor
			};
			Vertex v2 = {
				glm::vec3((float)(CELL_SIZE * x + CELL_SIZE), (float)(CELL_SIZE * y), 0.0f),
				defaultColor
			};
			Vertex v3 = {
				glm::vec3((float)(CELL_SIZE * x + CELL_SIZE), (float)(CELL_SIZE * y + CELL_SIZE), 0.0f),
				defaultColor
			};
			Vertex v4 = {
				glm::vec3((float)(CELL_SIZE * x), (float)(CELL_SIZE * y + CELL_SIZE), 0.0f),
				defaultColor
			};

			_vertices[vertexNb * 4] = v1;
			_vertices[vertexNb * 4 + 1] = v2;
			_vertices[vertexNb * 4 + 2] = v3;
			_vertices[vertexNb * 4 + 3] = v4;
		}
	}
}

void GridRenderer::updateVerticesColor()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int vertexNb = y * WIDTH + x;

			glm::vec3 randomColor = glm::vec3(
				(float)(rand() % 101) / 100.0f,
				(float)(rand() % 101) / 100.0f,
				(float)(rand() % 101) / 100.0f
			);
			_vertices[vertexNb * 4].Color = randomColor;
			_vertices[vertexNb * 4 + 1].Color = randomColor;
			_vertices[vertexNb * 4 + 2].Color = randomColor;
			_vertices[vertexNb * 4 + 3].Color = randomColor;
		}
	}
}

void GridRenderer::render(ShaderProgram& program)
{
	glBindVertexArray(_vao);

	program.useProgram();

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
	program.setMat4("projection", projection);

	program.setMat4("view", glm::mat4(1.0f));

	program.setMat4("transform", glm::mat4(1.0f));

	updateVerticesColor();

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4 * WIDTH * HEIGHT, _vertices);


	glDrawElements(GL_TRIANGLES, 6 * WIDTH * HEIGHT, GL_UNSIGNED_INT, nullptr);
}
