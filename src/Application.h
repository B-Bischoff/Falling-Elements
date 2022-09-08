#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include <iostream>

#include "ShaderProgram.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
};

class Application {
private:
	//const int WIN_WIDTH, WIN_HEIGHT;

	GLFWwindow* _window;
	
	void loop();

public:
	Application();
};
