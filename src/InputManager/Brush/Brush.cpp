#include "Brush.h"
#include "SquareBrush.h"
#include "CircleBrush.h"

Cell** Brush::_cells = nullptr;
int Brush::_selectedElement = 0;
int Brush::CELL_WIDTH = 0;
int Brush::CELL_HEIGHT = 0;
int Brush::CELL_SIZE = 0;
int Brush::brushSize = 5;

Brush::Brush(const CellsArrayData& cellsArrayData)
{
	_cells = cellsArrayData.cells;
	CELL_WIDTH = cellsArrayData.CELL_WIDTH;
	CELL_HEIGHT = cellsArrayData.CELL_HEIGHT;
	CELL_SIZE = cellsArrayData.CELL_SIZE;
}
void Brush::draw(const int& brushIndex, const glm::vec2& mousePos, const int& selectedElement)
{
	_selectedElement = selectedElement; // Update selected element
	glm::vec2 originCell = { // Convert mouse coordinates from pixels to cell coordinates
		mousePos.x / CELL_SIZE,
		mousePos.y / CELL_SIZE
	};

	switch (brushIndex)
	{
	case 0: SquareBrush::draw(originCell); break;
	case 1: CircleBrush::draw(originCell); break;
	default: break;
	}
}

void Brush::updateCursor(const int& brushIndex, GLFWwindow* window)
{
	switch (brushIndex)
	{
		case 0: SquareBrush::updateCursor(window); break;
		case 1: CircleBrush::updateCursor(window); break;
		default: break;
	}
}

void Brush::setCursorPixelColor(unsigned char* pixel, int r, int g, int b, int a)
{
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
	pixel[3] = a;
}

void Brush::setCursorCross(const int& cursorLength, unsigned char* pixels)
{
	const int N = cursorLength;
	if (N > 20)
	{
		const int CROSS_SIZE = N * 0.49f;
		for (int y = CROSS_SIZE * 4; y <= (N - CROSS_SIZE) * 4; y += 4)
			setCursorPixelColor(&(pixels[N * y + N * 2]), 0xff, 0xff, 0xff, 0xff);
		for (int x = CROSS_SIZE * 4; x <= (N - CROSS_SIZE) * 4; x += 4)
			setCursorPixelColor(&(pixels[(N * N * 2) + x]), 0xff, 0xff, 0xff, 0xff);
	}
}

void Brush::applyCursor(const glm::vec2& cursorDimensions, unsigned char* pixels, GLFWwindow* window)
{
	GLFWimage image;
	image.width = cursorDimensions.x;
	image.height = cursorDimensions.y;
	image.pixels = pixels;

	GLFWcursor* cursor = glfwCreateCursor(&image, brushSize * CELL_SIZE / 2, brushSize * CELL_SIZE / 2);
	if (cursor != nullptr)
		glfwSetCursor(window, cursor);
	else
		std::cerr << "Cursor creation failed." << std::endl;
}

const bool Brush::isInCellBoundaries(const double& x, const double& y)
{
	return (x >= 0 && x < CELL_WIDTH) && (y >= 0 && y < CELL_HEIGHT);
}

const bool Brush::isInCellBoundaries(const glm::vec2& pos)
{
	return (pos.x >= 0 && pos.x < CELL_WIDTH) && (pos.y >= 0 && pos.y < CELL_HEIGHT);
}
