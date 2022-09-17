#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class WaterBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell *_target;

public:
	WaterBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~WaterBehavior() { };

	void update()
	{
		_target = nullptr;
		_x = _cell->getPosition().x;
		_y = _cell->getPosition().y;

		_random = (rand() % 2) * 2 - 1; // 'random' can be -1 or 1

		if (_y < _cell->getHeight() - 1)
		{
			checkBelowCells();
			if (targetFound() == false)
				checkAdjacentBelowCells();
		}
		if (targetFound())
			updateVelocity();

		if (targetFound() == false)
			checkAdajacentCells();

		if (targetFound() == true)
		{
			_cell->swapCell(*_target);
		}

		if (targetFound() == false && cellHasVelocity() == true)
			releaseRemainingVelocity();
	}

private:
	void checkBelowCells()
	{
		for (int i = 0; i <= _cell->getVelocity().y; i++)
		{
			if ((_y + i + 1) < _cell->getHeight() && _cells[_y + i + 1][_x].getType() < CellType::Liquid)
				_target = &(_cells[_y + i + 1][_x]);
			else
				break;
		}
	}

	void checkAdjacentBelowCells()
	{
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y + 1][_x - _random].getType() < CellType::Liquid)
			_target = &(_cells[_y + 1][_x - _random]);
		else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y + 1][_x + _random].getType() < CellType::Liquid)
			_target = &(_cells[_y + 1][_x + _random]);
	}

	void checkAdajacentCells()
	{
		if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y][_x + _random].getType() < CellType::Liquid)
			_target = &(_cells[_y][_x + _random]);
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y][_x - _random].getType() < CellType::Liquid)
			_target = &(_cells[_y][_x - _random]);
	}

	void updateVelocity()
	{
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.1f));
	};

	void releaseRemainingVelocity()
	{
		float yVelocity = _cell->getVelocity().y;
		_cell->setVelocity(glm::vec2(yVelocity * _random / 1.0f, yVelocity / 1.0f));
		_cell->setMovementBehavior(new ParticleBehavior(_cell, *this));
	}

	const bool targetFound()
	{
		return _target;
	}

	const bool cellHasVelocity()
	{
		return _cell->getVelocity() != glm::vec2(0.0f);
	}
};
