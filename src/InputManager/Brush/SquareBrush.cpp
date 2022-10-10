#include "SquareBrush.h"

SquareBrush::SquareBrush(const CellsArrayData& cellsArrayData)
	: Brush(cellsArrayData)
{
}

void SquareBrush::draw(const glm::vec2& originCell)
{
	for (int y = originCell.y - brushSize / 2.0f; y <= originCell.y + brushSize / 2.0f - 1; y++)
	{
		for (int x = originCell.x - brushSize / 2.0f; x <= originCell.x + brushSize / 2.0f - 1; x++)
		{
			if (isInCellBoundaries(x, y))
			{
				Cell& cell = _cells[y][x];
				CellFactory::configureCell(cell, _selectedElement);
			}
		}
	}
}

void SquareBrush::updateCursor(GLFWwindow* window)
{
	const int N = brushSize * CELL_SIZE;
	unsigned char pixels[N * N * 4];

	for (int y = 0; y < N * 4; y += 4)
	{
		for (int x = 0; x < N * 4; x += 4)
		{
			if (x == 0 || y == 0 || x == N * 4 - 4 || y == N * 4 - 4)
				setCursorPixelColor(&(pixels[N * y + x]), 0xff, 0xff, 0xff, 0xff);
			else
				setCursorPixelColor(&(pixels[N * y + x]), 0x00, 0x00, 0x00, 0x00);
		}
	}

	setCursorCross(N, pixels);
	applyCursor(glm::vec2(N, N), pixels, window);
}
