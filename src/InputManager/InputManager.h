#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../Cell/Cell.h"
#include "../Cell/Factory/CellFactory.h"
#include "../Application.h"
#include "Brush/Brush.h"

struct WindowData;
struct CellsArrayData;

class InputManager {
private:
	const int WIN_WIDTH, WIN_HEIGHT;
	const int CELL_SIZE;
	const int CELL_WIDTH = WIN_WIDTH / CELL_SIZE;
	const int CELL_HEIGHT = WIN_HEIGHT / CELL_SIZE;

	GLFWwindow& _window;

	Cell** _cells;
	int& _selectedElement;
	int& _selectedBrush;
	Cell** _hoveredCell;

	double _mouseX, _mouseY;

	void updateMousePosition();
	void putCells();
	void updateHoveredCell();

	const bool isInCellsBoundaries(const double& x, const double& y) const;
	const bool isInScreenBoundaries(const double& x, const double& y) const;
	const bool isMouseOverUI() const;

public:
	InputManager(const WindowData& windowData, const CellsArrayData& cellsArrayData, int& selectedElement, int& selectedBrush, Cell** hoveredCell);

	void update();
};
