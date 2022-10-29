#include "InputManager.h"

InputManager::InputManager(const WindowData& windowData, const CellsArrayData& cellsArrayData, int& selectedElement, int& selectedBrush, Cell** hoveredCell)
	: _cells(cellsArrayData.cells), CELL_SIZE(cellsArrayData.CELL_SIZE), WIN_WIDTH(windowData.WIN_WIDTH), WIN_HEIGHT(windowData.WIN_HEIGHT), 
		_window(windowData.window), _selectedElement(selectedElement), _selectedBrush(selectedBrush), _hoveredCell(hoveredCell)
{
	static Brush brush(cellsArrayData);
}

InputManager::InputManager(const WindowData& windowData, const CellsArrayData& cellsArrayData, const SimulationData& simulationData)
	: _cells(cellsArrayData.cells), CELL_SIZE(cellsArrayData.CELL_SIZE), WIN_WIDTH(windowData.WIN_WIDTH - windowData.UI_WIDTH), WIN_HEIGHT(windowData.WIN_HEIGHT), 
		_window(windowData.window), _selectedElement(simulationData.selectedElement), _selectedBrush(simulationData.selectedBrush), _hoveredCell(simulationData.hoveredCell)
{
	static Brush brush(cellsArrayData);
}

void InputManager::update()
{
	updateMousePosition();
	putCells();
	updateHoveredCell();
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

void InputManager::updateHoveredCell()
{
	int x = _mouseX / CELL_SIZE;
	int y = _mouseY / CELL_SIZE;
	if (isInCellsBoundaries(x, y))
		*_hoveredCell = &_cells[y][x];
	else
		*_hoveredCell = nullptr;
}

const bool InputManager::isInCellsBoundaries(const double& x, const double& y) const
{
	return (x >= 0 && x < CELL_WIDTH) && (y >= 0 && y < CELL_HEIGHT);
}

const bool InputManager::isInScreenBoundaries(const double& x, const double& y) const
{
	return (x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT);
}

const bool InputManager::isMouseOverUI() const
{
	ImGuiIO& io = ImGui::GetIO();
	return (io.WantCaptureMouse);
}
