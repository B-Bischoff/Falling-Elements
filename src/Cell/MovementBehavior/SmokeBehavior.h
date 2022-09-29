#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class Cell;

class SmokeBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	SmokeBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~SmokeBehavior() { };

	void update()
	{
		_target = nullptr;
		_x = _cell->getPosition().x;
		_y = _cell->getPosition().y;

		_random = (rand() % 2) * 2 - 1;

		checkUpCell();
		if (targetFound() == false)
			checkAdjacentUpCells();
		
		if (targetFound() == true)
			_cell->swapCell(*_target);

		static int test = 0;

		if (test >= 20000)
		{
			//CellFactory::configureWaterCell(*_cell);
		}

		test++;
	}

	void checkUpCell()
	{
		if (_y > 0 && _cells[_y - 1][_x].getType() <= CellType::Gazeous && _cell->_density < _cells[_y - 1][_x]._density)
			_target = &(_cells[_y - 1][_x]);
	}

	void checkAdjacentUpCells()
	{
		if (_y > 0)
		{
			if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y - 1][_x - _random].getType() <= CellType::Gazeous && _cell->_density < _cells[_y - 1][_x - _random]._density)
				_target = &(_cells[_y - 1][_x - _random]);
			else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y - 1][_x + _random].getType() <= CellType::Gazeous && _cell->_density < _cells[_y - 1][_x + _random]._density)
				_target = &(_cells[_y - 1][_x + _random]);

		}
	}

	const bool targetFound()
	{
		return _target;
	}

};
