#include "GridRenderer.h"

GridRenderer::~GridRenderer()
{
	delete [] _indices;
	delete [] _vertices;
}

GridRenderer::GridRenderer(const CellsArrayData& cellsArrayData, const WindowData& windowData, int& selectedFilter)
	: CELL_WIDTH(cellsArrayData.CELL_WIDTH), CELL_HEIGHT(cellsArrayData.CELL_HEIGHT),
	CELL_SIZE(cellsArrayData.CELL_SIZE), WIN_HEIGHT(windowData.WIN_HEIGHT),
	WIN_WIDTH(windowData.WIN_WIDTH), _selectedFilter(selectedFilter),
	_indices(nullptr), _vertices(nullptr)
{
	initializeMemory();
	generateIndices();
	initializeOpenglObjects();
	initializeVertexPositions();
}

void GridRenderer::initializeMemory()
{
	_indices = new uint32_t [CELL_WIDTH * CELL_HEIGHT * 6];
	_vertices = new Vertex [CELL_WIDTH * CELL_HEIGHT * 4];

	if (_vertices == nullptr || _indices == nullptr)
	{
		std::cerr << "[GridRenderer] Initialization failed." << std::endl;
		std::cin.get();
		exit (1);
	}
}

void GridRenderer::generateIndices()
{
	const int VERT_NB = CELL_WIDTH * CELL_HEIGHT * 6;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * CELL_WIDTH * CELL_HEIGHT, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * CELL_WIDTH * CELL_HEIGHT * 6, _indices, GL_STATIC_DRAW);
}

void GridRenderer::initializeVertexPositions()
{
	const glm::vec3 defaultColor = glm::vec3(0.2f, 0.0f, 0.2f);

	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			// "(HEIGHT - 1 - y)" is used to reverse the y axis
			// So that cells[0][0] is diplayed at the screen top left instead of screen bottom left
			int vertexNb = (CELL_HEIGHT - 1 - y) * CELL_WIDTH + x;

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

			_vertices[vertexNb * 4] = v1; // Top left 
			_vertices[vertexNb * 4 + 1] = v2; // Top right 
			_vertices[vertexNb * 4 + 2] = v3; // Bottom right 
			_vertices[vertexNb * 4 + 3] = v4; // Bottom left 
		}
	}
}

void GridRenderer::render(ShaderProgram& program, Cell** cells)
{
	glBindVertexArray(_vao);

	program.useProgram();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIN_WIDTH), 0.0f, static_cast<float>(WIN_HEIGHT), -1.0f, 1.0f);
	program.setMat4("projection", projection);

	program.setMat4("view", glm::mat4(1.0f));

	program.setMat4("transform", glm::mat4(1.0f));

	switch (_selectedFilter)
	{
	case 0: updateColorFromColor(cells); break;
	case 1: updateColorFromVelocity(cells); break;
	case 2: updateColorFromTemperature(cells); break;
	default: updateColorFromRandom(cells); break;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4 * CELL_WIDTH * CELL_HEIGHT, _vertices);


	glDrawElements(GL_TRIANGLES, 6 * CELL_WIDTH * CELL_HEIGHT, GL_UNSIGNED_INT, nullptr);
}

void GridRenderer::updateColorFromRandom(Cell** _cells)
{
	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			int vertexNb = y * CELL_WIDTH + x;

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

void GridRenderer::updateColorFromColor(Cell** _cells)
{
	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			int vertexNb = y * CELL_WIDTH + x;

			glm::vec3 color = _cells[y][x].getColor();

			_vertices[vertexNb * 4].Color = color;
			_vertices[vertexNb * 4 + 1].Color = color;
			_vertices[vertexNb * 4 + 2].Color = color;
			_vertices[vertexNb * 4 + 3].Color = color;
		}
	}
}

void GridRenderer::updateColorFromVelocity(Cell** _cells)
{
	const glm::vec3 VELOCITY(0.0f, 1.0f, 0.0f);
	const glm::vec3 NO_VELOCITY(0.0f, 0.0f, 0.0f);

	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			int vertexNb = y * CELL_WIDTH + x;

			glm::vec3 color;
			if (_cells[y][x].getVelocity() == glm::vec2(0.0f))
				color = NO_VELOCITY / 2.0f;
			else
				color = VELOCITY / 2.0f;

			if (_cells[y][x].getVelocity().x > 0.0f)
				color = glm::vec3(0.0f, 1.0f, 0.0f);
			else if (_cells[y][x].getVelocity().x < 0.0f)
				color = glm::vec3(1.0f, 0.0f, 0.0f);
			else if (_cells[y][x].getVelocity().y != 0.0f)
				color = glm::vec3(1.0f, 1.0f, 1.0f);
			else
				color = NO_VELOCITY;

			color = color * 0.6f + rgbToGrayscale(_cells[y][x].getColor()) * 0.40f;

			_vertices[vertexNb * 4].Color = color;// + _cells[y][x].getColor() / 2.0f;
			_vertices[vertexNb * 4 + 1].Color = color;// + _cells[y][x].getColor() / 2.0f;
			_vertices[vertexNb * 4 + 2].Color = color;// + _cells[y][x].getColor() / 2.0f;
			_vertices[vertexNb * 4 + 3].Color = color;// + _cells[y][x].getColor() / 2.0f;
		}
	}
}

void GridRenderer::updateColorFromTemperature(Cell** _cells)
{
	const glm::vec3 HOT(1.0f, 0.0f, 0.0f);
	const glm::vec3 COLD(0.0f, 0.0f, 1.0f);
	const double MIN = -100.0;
	const double MAX = 200.0;

	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			int vertexNb = y * CELL_WIDTH + x;

			double temperature = _cells[y][x]._temperature;
			double t = (temperature - MIN) / (MAX - MIN); // inv lerp
			double r = (HOT.r - COLD.r) * t + COLD.r;
			double g = (HOT.g - COLD.g) * t + COLD.g;
			double b = (HOT.b - COLD.b) * t + COLD.b;
			glm::vec3 color = glm::vec3(r, g, b);
			color = color * 0.6f + rgbToGrayscale(_cells[y][x].getColor()) * 0.40f;

			_vertices[vertexNb * 4].Color = color;
			_vertices[vertexNb * 4 + 1].Color = color;
			_vertices[vertexNb * 4 + 2].Color = color;
			_vertices[vertexNb * 4 + 3].Color = color;
		}
	}
}

const glm::vec3 GridRenderer::rgbToGrayscale(const glm::vec3& color) const
{
	float value = color.r * 0.3f + color.g * 0.59f + color.b * 0.11f;
	return glm::vec3(value);
}
