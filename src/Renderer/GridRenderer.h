#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <stdlib.h>

#include "../ShaderProgram.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
};

class GridRenderer {
private:
	const int WIDTH, HEIGHT;

	uint32_t* _indices;
	Vertex* _vertices;

	unsigned int _vbo, _vao, _ibo;

	void initializeMemory();
	void initializeOpenglObjects();
	void generateIndices();
	void initializeVertexPositions();

	void updateVerticesColor();

public:
	GridRenderer(const int& width, const int& height);
	~GridRenderer();

	void render(ShaderProgram& program);
};
