#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../Cell/Cell.h"
#include "../Cell/Factory/CellFactory.h"

class InputManager {
private:
	const int WIN_WIDTH, WIN_HEIGHT;
	const int CELL_SIZE;
	const int CELL_WIDTH = WIN_WIDTH / CELL_SIZE;
	const int CELL_HEIGHT = WIN_HEIGHT / CELL_SIZE;

	GLFWwindow& _window;

	Cell** _cells;
	int& _selectedElement;

	double _mouseX, _mouseY;

	void updateMousePosition();
	void putCells();

	const bool isInCellsBoundaries(const double& x, const double& y) const;

public:
	InputManager(Cell** cells, GLFWwindow& window, const int& winWidth, const int& winHeight, const int& cellSize, int& selectedElement);

	void update();
};
