#include "CircleBrush.h"

CircleBrush::CircleBrush(const CellsArrayData& cellsArrayData)
	: Brush(cellsArrayData)
{
	std::cout << "Circle Brush Init" << std::endl;
}

void CircleBrush::draw(const glm::vec2& originCell)
{
	const int DIAMETER = brushSize;
	const float RADIUS = static_cast<float>(DIAMETER) / 2.0f;
	for (int y = -RADIUS; y < RADIUS; y++)
	{
		for (int x = -RADIUS; x < RADIUS; x++)
		{
			const int LENGTH_SQUARED = abs(y*y+x*x);
			if (LENGTH_SQUARED < RADIUS*RADIUS)
			{
				if (isInCellBoundaries(originCell + glm::vec2(x, y)))
				{
					Cell& cell = _cells[(int)originCell.y + y][(int)originCell.x + x];
					CellFactory::configureCell(cell, _selectedElement);
				}
			}
		}
	}
}

void CircleBrush::updateCursor(GLFWwindow* window)
{
	const int N = brushSize * CELL_SIZE;
	unsigned char pixels[N * N * 4];

	const int RADIUS = static_cast<float>(N) / 2.0f;
	for (int y = 0; y < N * 4; y += 4)
	{
		for (int x = 0; x < N * 4; x += 4)
		{
			int dx = (x+2) - N * 2;
			int dy = (y+2) - N * 2;
			if (abs(dx*dx+dy*dy) >= (N * N * 4) - 10*N && abs(dx*dx+dy*dy) <= N * N * 4 + 10*N)
				setCursorPixelColor(&(pixels[N * y + x]), 0xff, 0xff, 0xff, 0xff);
			else
				setCursorPixelColor(&(pixels[N * y + x]), 0xff, 0xff, 0xff, 0x00);
		}
	}

	setCursorCross(N, pixels);
	applyCursor(glm::vec2(N, N), pixels, window);
}
