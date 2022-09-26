#pragma once

#include "glm/glm.hpp"

#include "InputManager.h"

struct CellsArrayData;

class Brush {
private:
	static Cell** _cells;
	static int CELL_WIDTH, CELL_HEIGHT, CELL_SIZE;
	static int _selectedElement;

	static void squareBrush(const glm::vec2& originCell);
	static void circleBrush(const glm::vec2& originCell);

	static const bool isInCellBoundaries(const double& x, const double& y);
	static const bool isInCellBoundaries(const glm::vec2& pos);

public:
	Brush(const CellsArrayData& cellsArrayData);

	static void draw(const int& brushIndex, const glm::vec2& mousePos, const int& selectedElement);

};
