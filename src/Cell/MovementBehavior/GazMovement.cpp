#include "GazMovement.h"

GazMovement::GazMovement(Cell* cell)
	: IMovementBehavior(cell)
{

}

void GazMovement::update()
{
	_target = nullptr;
	_x = _cell->getPosition().x;
	_y = _cell->getPosition().y;
	_cell->setVelocity(glm::vec2(0.0f));

	if (_y > 0)
	{
		_random = (rand() % 2) * 2 - 1;

		checkUpCell();
		checkAdjacentUpCells();
		checkAdjacentCells();

		if (targetFound() == true)
			_cell->swapCell(*_target);
	}
}

void GazMovement::checkUpCell()
{
	Cell& upCell = _cells[_y - 1][_x];

	if (canSwap(upCell))
		_target = &upCell;
}

void GazMovement::checkAdjacentUpCells()
{
	if (_x + _random >= 0 && _x + _random < _cell->getWidth())
{
		Cell& cell = _cells[_y - 1][_x + _random];
		if (canSwap(cell))
		{
			_target = &cell;
			return;
		}
	}
	if (_x - _random >= 0 && _x - _random < _cell->getWidth())
	{
		Cell& cell = _cells[_y - 1][_x - _random];
		if (canSwap(cell))
			_target = &cell;
	}
}

void GazMovement::checkAdjacentCells()
{
	if (_x + _random >= 0 && _x + _random < _cell->getWidth())
	{
		Cell& cell = _cells[_y][_x + _random];
		if (canSwap(cell))
		{
			_target = &cell;
			return;
		}
	}
	if (_x - _random >= 0 && _x - _random < _cell->getWidth())
	{
		Cell& cell = _cells[_y][_x - _random];
		if (canSwap(cell))
			_target = &cell;
	}
}

const bool GazMovement::canSwap(const Cell& cell) const
{
	if (cell.getType() == CellType::Gazeous)
	{
		if (cell._density > _cell->_density)
			return true;
		else if (cell._density < _cell->_density)
			return false;

		if (targetFound() == false)
			return true;
		else
		{
			if (cell._nextTemperature < _target->_nextTemperature)
				return true;
			else
				return false;
		}
		return true;
	}
	else
		return false;
}

const bool GazMovement::targetFound() const
{
	return _target;
}
