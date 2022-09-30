#include "SmokeBehavior.h"

SmokeBehavior::SmokeBehavior(Cell* cell)
	: IMovementBehavior(cell)
{

}

void SmokeBehavior::update()
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

	if (_test >= 20)
	{
		CellFactory::configureWaterCell(*_cell);
	}

	_test += 1;
}

void SmokeBehavior::checkUpCell()
{

	if (_y > 0 && _cells[_y - 1][_x].getType() <= CellType::Gazeous && _cell->_density < _cells[_y - 1][_x]._density)
		_target = &(_cells[_y - 1][_x]);
}

void SmokeBehavior::checkAdjacentUpCells()
{
	if (_y > 0)
	{
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y - 1][_x - _random].getType() <= CellType::Gazeous && _cell->_density < _cells[_y - 1][_x - _random]._density)
			_target = &(_cells[_y - 1][_x - _random]);
		else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y - 1][_x + _random].getType() <= CellType::Gazeous && _cell->_density < _cells[_y - 1][_x + _random]._density)
			_target = &(_cells[_y - 1][_x + _random]);

	}
}

const bool SmokeBehavior::targetFound()
{
	return _target;
}
