#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <stdlib.h>

#include "../ShaderProgram.h"
#include "../Cell/Cell.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
};

class GridRenderer {
private:
	const int WIDTH, HEIGHT, CELL_SIZE;

	int& _selectedFilter;

	uint32_t* _indices;
	Vertex* _vertices;

	unsigned int _vbo, _vao, _ibo;

	void initializeMemory();
	void initializeOpenglObjects();
	void generateIndices();
	void initializeVertexPositions();

	void updateColorFromRandom(Cell** cells); // Test method
	void updateColorFromColor(Cell** cells);
	void updateColorFromVelocity(Cell** cells);
	void updateColorFromTemperature(Cell** cells);

public:
	GridRenderer(const int& width, const int& height, const int& cellSize, int& selectedFilter);

	~GridRenderer();

	void render(ShaderProgram& program, Cell** cells);
};
