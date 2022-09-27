#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <random>

#include "ShaderProgram.h"
#include "UI/UserInterface.h"
#include "Renderer/GridRenderer.h"
#include "InputManager/InputManager.h"
#include "Cell/Cell.h"
#include "Cell/Factory/CellFactory.h"

struct WindowData {
	GLFWwindow& window;
	const int WIN_WIDTH;
	const int WIN_HEIGHT;
};

struct CellsArrayData {
	const int CELL_SIZE;
	const int CELL_WIDTH;
	const int CELL_HEIGHT;
	Cell** cells;
};

class Application {
private:
	const int WIN_WIDTH, WIN_HEIGHT;
	const int CELL_SIZE = 4;
	const int CELL_WIDTH = WIN_WIDTH / CELL_SIZE;
	const int CELL_HEIGHT = WIN_HEIGHT / CELL_SIZE;
	const int RANDOM_SETS_NB = 100;

	int _selectedElement;
	int _selectedBrush;

	std::vector<int>* _randomSets;
	int _currentRandomSet;

	GLFWwindow* _window;
	Cell** _cells;

	void loop();
	void generateRandomSets();

public:
	Application(const int& width, const int& height);
	~Application();
};
