#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class SandBehavior : public IMovementBehavior {
private:

public:
	SandBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~SandBehavior() {};

	void update()
	{
		int x = _cell->getPosition().x;
		int y = _cell->getPosition().y;

		if (y < _cell->getHeight() - 1)
		{
			Cell* target = nullptr;

			int random = rand() % 2;
			random = random * 2 - 1;

			if (_cells[y + 1][x].getType() < CellType::Solid)
				target = &(_cells[y + 1][x]);
			else if (x - random >= 0 && x - random < _cell->getWidth() && _cells[y + 1][x - random].getType() < CellType::Solid)
				target = &(_cells[y + 1][x - random]);
			else if (x + random >= 0 && x + random < _cell->getWidth() && _cells[y + 1][x + random].getType() < CellType::Solid)
				target = &(_cells[y + 1][x + random]);

			if (target != nullptr)
			{
				_cell->swapCell(*target);
			}
		}
	};

};
