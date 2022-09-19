#include "InputManager.h"

InputManager::InputManager(Cell** cells, GLFWwindow& window, const int& winWidth, const int& winHeight, const int& cellSize, int& selectedElement)
	: _cells(cells), _window(window), WIN_WIDTH(winWidth), WIN_HEIGHT(winHeight), CELL_SIZE(cellSize), _selectedElement(selectedElement)
{

}


void InputManager::update()
{
	updateMousePosition();
	putCells();
}

void InputManager::updateMousePosition()
{
	glfwGetCursorPos(&_window, &_mouseX, &_mouseY);
}

void InputManager::putCells()
{
	if (glfwGetMouseButton(&_window, GLFW_MOUSE_BUTTON_LEFT))
	{
		int cellX = _mouseX / CELL_SIZE;
		int cellY = _mouseY / CELL_SIZE;

		if (isInCellsBoundaries(cellX, cellY))
		{
			Cell& cell = _cells[cellY][cellX];
			CellFactory::configureCell(cell, _selectedElement);
		}

		/*
		// Classic paint brush
		const int BRUSH_SIZE = 20;
		for (int y = cellY - BRUSH_SIZE / 2.0f; y < cellY + BRUSH_SIZE / 2.0f - 1; y++)
		{
			for (int x = cellX - BRUSH_SIZE / 2.0f; x < cellX + BRUSH_SIZE / 2.0f - 1; x++)
			{
				if (isInCellsBoundaries(x, y))
				{
					Cell& cell = _cells[y][x];
					CellFactory::configureCell(cell, _selectedElement);
				}
			}
		}
		*/
	}
}

const bool InputManager::isInCellsBoundaries(const double& x, const double& y) const
{
	return (x >= 0 && x < CELL_WIDTH) && (y >= 0 && y < CELL_HEIGHT);
}
