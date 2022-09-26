#include "Brush.h"

Cell** Brush::_cells = nullptr;
int Brush::_selectedElement = 0;
int Brush::CELL_WIDTH = 0;
int Brush::CELL_HEIGHT = 0;
int Brush::CELL_SIZE = 0;

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

	squareBrush(originCell);

	switch (brushIndex)
	{
	case 0: squareBrush(originCell); break;
	case 1: circleBrush(originCell); break;
	default: break;
	}
}

void Brush::squareBrush(const glm::vec2& originCell)
{
	const int BRUSH_SIZE = 10;
	for (int y = originCell.y - BRUSH_SIZE / 2.0f; y <= originCell.y + BRUSH_SIZE / 2.0f - 1; y++)
	{
		for (int x = originCell.x - BRUSH_SIZE / 2.0f; x <= originCell.x + BRUSH_SIZE / 2.0f - 1; x++)
		{
			if (isInCellBoundaries(x, y))
			{
				Cell& cell = _cells[y][x];
				CellFactory::configureCell(cell, _selectedElement);
			}
		}
	}
}

void Brush::circleBrush(const glm::vec2& originCell)
{
	const int DIAMETER = 50;
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

void Brush::updateCursor(const int& brushIndex, GLFWwindow* window)
{
	switch (brushIndex)
	{
		case 0: updateSquareBrushCursor(window); break;
		case 1: updateCircleBrushCursor(window); break;
		default: break;
	}
}

void Brush::updateSquareBrushCursor(GLFWwindow* window)
{
	const int N = 20;
	unsigned char pixels[N * N * 4];

	for (int y = 0; y < N * 4; y += 4)
	{
		for (int x = 0; x < N * 4; x += 4)
		{
			if (x == 0 || y == 0 || x == N * 4 - 4 || y == N * 4 - 4)
				setCursorPixelColor(&(pixels[N * y + x]), 0xff, 0xff, 0xff, 0xff);
			else
				setCursorPixelColor(&(pixels[N * y + x]), 0x00f, 0x00f, 0x00f, 0x00f);
		}
	}

	applyCursor(glm::vec2(N, N), pixels, window);
}

void Brush::updateCircleBrushCursor(GLFWwindow* window)
{
	const int N = 15;
	unsigned char pixels[N * N * 4];

	for (int y = 0; y < N * 4; y += 4)
	{
		for (int x = 0; x < N * 4; x += 4)
		{
			if (x == 0 || y == 0 || x == N * 4 - 4 || y == N * 4 - 4)
				setCursorPixelColor(&(pixels[N * y + x]), 0xff, 0xff, 0xff, 0xff);
			else
				setCursorPixelColor(&(pixels[N * y + x]), 0x00f, 0x00f, 0x00f, 0x00f);
		}
	}

	applyCursor(glm::vec2(N, N), pixels, window);
}

void Brush::setCursorPixelColor(unsigned char* pixel, int r, int g, int b, int a)
{
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
	pixel[3] = a;
}

void Brush::applyCursor(const glm::vec2& cursorDimensions, unsigned char* pixels, GLFWwindow* window)
{
	GLFWimage image;
	image.width = cursorDimensions.x;
	image.height = cursorDimensions.y;
	image.pixels = pixels;

	GLFWcursor* cursor = glfwCreateCursor(&image, 11, 11);
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
