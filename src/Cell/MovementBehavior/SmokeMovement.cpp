#include "SmokeMovement.h"

SmokeMovement::SmokeMovement(Cell* cell)
	: IMovementBehavior(cell)
{
}

void SmokeMovement::update()
{
	_target = nullptr;
	_x = _cell->getPosition().x;
	_y = _cell->getPosition().y;

	_random = (rand() % 2) * 2 - 1;

		checkAdjacentUpCells();
	if (targetFound() == false || _target->_density == _cell->_density)
		checkUpCell();
	if (targetFound() == false || _target->_density == _cell->_density)
		checkAdjacentCells();

	if (targetFound() == true)
		_cell->swapCell(*_target);
	_cell->setVelocity(glm::vec2(0.0f));
}

void SmokeMovement::checkUpCell()
{

	if (_y > 0 && _cells[_y - 1][_x].getType() <= CellType::Liquid && canSwap(_cells[_y - 1][_x]))
		_target = &(_cells[_y - 1][_x]);
}

void SmokeMovement::checkAdjacentUpCells()
{
	if (_y > 0)
	{
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && canSwap(_cells[_y - 1][_x]))
			_target = &(_cells[_y - 1][_x - _random]);
		else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && canSwap(_cells[_y - 1][_x + _random]))
			_target = &(_cells[_y - 1][_x + _random]);
	}
}

void SmokeMovement::checkAdjacentCells()
{
	if (_x - _random >= 0 && _x - _random < _cell->getWidth() && canSwap(_cells[_y][_x - _random]))
		_target = &(_cells[_y][_x - _random]);
	else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && canSwap(_cells[_y][_x + _random]))
		_target = &(_cells[_y][_x + _random]);
}

const bool SmokeMovement::targetFound()
{
	return _target;
}

const bool SmokeMovement::canSwap(const Cell& cell) const
{
	if (cell.getType() == CellType::Liquid)
		return true;
	else if (cell.getType() == CellType::Gazeous)
	{
		if (_cell->_density < cell._density)
			return true;
		else if (_cell->_temperature > cell._temperature)
			return true;
	}
	return false;
}

