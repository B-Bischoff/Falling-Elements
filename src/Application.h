#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <numeric>

#include "ShaderProgram.h"
#include "Renderer/GridRenderer.h"
#include "Cell/Cell.h"
#include "Cell/Factory/CellFactory.h"

class Application {
private:
	const int WIN_WIDTH, WIN_HEIGHT;

	GLFWwindow* _window;
	Cell** _cells;

	void loop();

public:
	Application(const int& width, const int& height);
	~Application();
};
