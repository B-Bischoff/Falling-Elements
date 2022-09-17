#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleBehavior.h"

class IMovementBehavior;

class SandBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	SandBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~SandBehavior() {};

	void update()
	{
		_target = nullptr;
		_x = _cell->getPosition().x;
		_y = _cell->getPosition().y;

		if (_y < _cell->getHeight() - 1)
		{
			_random = (rand() % 2) * 2 - 1; // 'random' can be -1 or 1

			checkBelowCells();
			if (targetFound() == false)
				CheckAdjacentBelowCells();

			if (targetFound() == true)
			{
				updateVelocity();
				_cell->swapCell(*_target);
			}
		}

		if (targetFound() == false && cellHasVelocity() == true)
			releaseRemainingVelocity();
	}

private:
	void checkBelowCells()
	{
		for (int i = 0; i <= _cell->getVelocity().y; i++)
		{
			if ((_y + i + 1) < _cell->getHeight() && _cells[_y + i + 1][_x].getType() < CellType::Solid)
				_target = &(_cells[_y + i + 1][_x]);
			else
				break;
		}
	};

	void CheckAdjacentBelowCells()
	{
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y + 1][_x - _random].getType() < CellType::Solid)
			_target = &(_cells[_y + 1][_x - _random]);
		else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y + 1][_x + _random].getType() < CellType::Solid)
			_target = &(_cells[_y + 1][_x + _random]);
	};

	void updateVelocity()
	{
		if (_target->getType() == CellType::Gazeous) // Accelerate in free falling
			_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.1f));
		else if (_target->getType() == CellType::Liquid && _cell->getVelocity().y > 0.4f) // Get slow done by liquid
			_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, -0.4f));
	};

	void releaseRemainingVelocity()
	{
		float yVelocity = _cell->getVelocity().y;
		_cell->setVelocity(glm::vec2(yVelocity * _random / 3.0f, yVelocity / 3.0f));
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
