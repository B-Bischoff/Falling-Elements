#pragma once

#include "Brush.h"

class Brush;

class CircleBrush : public Brush {
private:

public:
	CircleBrush(const CellsArrayData& cellsArrayData);

	static void draw(const glm::vec2& originCell);
	static void updateCursor(GLFWwindow* window);
};
