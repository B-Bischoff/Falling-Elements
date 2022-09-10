#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

#include "ShaderProgram.h"
#include "Renderer/GridRenderer.h"

class Application {
private:
	const int WIN_WIDTH, WIN_HEIGHT;

	GLFWwindow* _window;

	void loop();
	uint32_t* generateIndices(const int& width, const int& height);

public:
	Application(const int& width, const int& height);
};
