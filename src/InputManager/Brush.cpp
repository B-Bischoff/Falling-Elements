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
	const int BRUSH_SIZE = 5;
	for (int y = originCell.y - BRUSH_SIZE / 2.0f; y < originCell.y + BRUSH_SIZE / 2.0f - 1; y++)
	{
		for (int x = originCell.x - BRUSH_SIZE / 2.0f; x < originCell.x + BRUSH_SIZE / 2.0f - 1; x++)
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

const bool Brush::isInCellBoundaries(const double& x, const double& y)
{
	return (x >= 0 && x < CELL_WIDTH) && (y >= 0 && y < CELL_HEIGHT);
}

const bool Brush::isInCellBoundaries(const glm::vec2& pos)
{
	return (pos.x >= 0 && pos.x < CELL_WIDTH) && (pos.y >= 0 && pos.y < CELL_HEIGHT);
}
