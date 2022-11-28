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
#include "UI/TextureLoader/TextureLoader.hpp"
#include "Renderer/GridRenderer.h"
#include "InputManager/InputManager.h"
#include "Cell/Cell.h"
#include "Cell/Factory/CellFactory.h"

struct WindowData {
	GLFWwindow& window;
	const int WIN_WIDTH;
	const int WIN_HEIGHT;
	const int UI_WIDTH;
};

struct CellsArrayData {
	const int CELL_SIZE;
	const int CELL_WIDTH;
	const int CELL_HEIGHT;
	Cell** cells;
};

struct SimulationData {
	int& selectedElement;
	int& selectedBrush;
	int& selectedFilter;
	float& simulationSpeed;
	Cell** hoveredCell;
};

class Application {
private:
	const int CELL_SIZE = 4;
	const int UI_WIDTH = 300;
	const int WIN_WIDTH, WIN_HEIGHT;
	const int CELL_WIDTH = (WIN_WIDTH - UI_WIDTH) / CELL_SIZE;
	const int CELL_HEIGHT = WIN_HEIGHT / CELL_SIZE;
	const int RANDOM_SETS_NB = 200;

	int _selectedElement;
	int _selectedBrush;
	int _selectedFilter;
	float _simulationSpeed;
	Cell* _hoveredCell;

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
