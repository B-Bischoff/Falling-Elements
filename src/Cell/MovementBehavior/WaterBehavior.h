#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class WaterBehavior : public IMovementBehavior {
private:

public:
	WaterBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~WaterBehavior() { };

	void update()
	{
		int x = _cell->getPosition().x;
		int y = _cell->getPosition().y;

		Cell* target = nullptr;

		int random = rand() % 2;
		random = random * 2 - 1;

		if (y < _cell->getHeight() - 1)
		{
			if (_cells[y + 1][x].getType() < CellType::Liquid)
				target = &(_cells[y + 1][x]);
			else if (x - random >= 0 && x - random < _cell->getWidth() && _cells[y + 1][x - random].getType() < CellType::Liquid)
				target = &(_cells[y + 1][x - random]);
			else if (x + random >= 0 && x + random < _cell->getWidth() && _cells[y + 1][x + random].getType() < CellType::Liquid)
				target = &(_cells[y + 1][x + random]);
		}
		if (target == nullptr)
		{
			if (x + random >= 0 && x + random < _cell->getWidth() && _cells[y][x + random].getType() < CellType::Liquid)
				target = &(_cells[y][x + random]);
			if (x - random >= 0 && x - random < _cell->getWidth() && _cells[y][x - random].getType() < CellType::Liquid)
				target = &(_cells[y][x - random]);
		}

		if (target != nullptr)
		{
			_cell->swapCell(*target);
			/*
			IMovementBehavior* temp = _cell->getMovementBehavior();

			// Replace current cell to air
			_cell->setColor(target->getColor());
			_cell->setType(target->getType());
			_cell->setMovementBehavior(target->getMovementBehavior());
			_cell->getMovementBehavior()->setCell(_cell);

			// Replace target to water
			target->setColor(glm::vec3(0.2f, 0.6f, 1.0f));
			target->setType(CellType::Liquid);
			target->setMovementBehavior(temp);
			target->getMovementBehavior()->setCell(target);
			*/
		}
	}
};
