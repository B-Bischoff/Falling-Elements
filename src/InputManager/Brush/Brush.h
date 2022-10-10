#pragma once

#include "glm/glm.hpp"

#include "../InputManager.h"

struct CellsArrayData;
class SquareBrush;

class Brush {
protected:
	static Cell** _cells;
	static int CELL_WIDTH, CELL_HEIGHT, CELL_SIZE;
	static int _selectedElement;

	static void setCursorPixelColor(unsigned char* pixel, int r, int g, int b, int a);
	static void setCursorCross(const int& cursorLength, unsigned char* pixels);
	static void applyCursor(const glm::vec2& cursorDimensions, unsigned char* pixels, GLFWwindow* window);

	static const bool isInCellBoundaries(const double& x, const double& y);
	static const bool isInCellBoundaries(const glm::vec2& pos);

public:
	Brush(const CellsArrayData& cellsArrayData);

	static void draw(const int& brushIndex, const glm::vec2& mousePos, const int& selectedElement);
	static void updateCursor(const int& brushIndex, GLFWwindow* window);

	static int brushSize;

};
