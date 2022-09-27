#include "InputManager.h"

InputManager::InputManager(const WindowData& windowData, const CellsArrayData& cellsArrayData, int& selectedElement, int& selectedBrush)
	: _cells(cellsArrayData.cells), CELL_SIZE(cellsArrayData.CELL_SIZE), WIN_WIDTH(windowData.WIN_WIDTH), WIN_HEIGHT(windowData.WIN_HEIGHT), 
		_window(windowData.window), _selectedElement(selectedElement), _selectedBrush(selectedBrush)
{
	static Brush brush(cellsArrayData);
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
	if (glfwGetMouseButton(&_window, GLFW_MOUSE_BUTTON_LEFT) && isMouseOverUI() == false)
	{
		Brush::draw(_selectedBrush, glm::vec2(_mouseX, _mouseY), _selectedElement);
	}
}

const bool InputManager::isInCellsBoundaries(const double& x, const double& y) const
{
	return (x >= 0 && x < CELL_WIDTH) && (y >= 0 && y < CELL_HEIGHT);
}

const bool InputManager::isMouseOverUI() const
{
	ImGuiIO& io = ImGui::GetIO();
	return (io.WantCaptureMouse);
}
