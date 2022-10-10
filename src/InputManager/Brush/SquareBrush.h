#pragma once

#include "Brush.h"

class Brush;

class SquareBrush : public Brush {
private:

public:
	SquareBrush(const CellsArrayData& cellsArrayData);

	static void draw(const glm::vec2& originCell);
	static void updateCursor(GLFWwindow* window);
};
