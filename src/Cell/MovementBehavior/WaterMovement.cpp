#include "WaterMovement.h"

WaterMovement::WaterMovement(Cell* cell)
	: IMovementBehavior(cell)
{

}

void WaterMovement::update()
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
		checkAdjacentCells();

	if (targetFound() == true)
	{
		_cell->swapCell(*_target);
	}

	if (targetFound() == false && cellHasVelocity() == true)
		releaseRemainingVelocity();
}

void WaterMovement::checkBelowCells()
{
	for (int i = 0; i <= _cell->getVelocity().y; i++)
	{
		if ((_y + i + 1) < _cell->getHeight() && canSwap(_cells[_y + i + 1][_x]))
			_target = &(_cells[_y + i + 1][_x]);
		else
			break;
	}
}

void WaterMovement::checkAdjacentBelowCells()
{
	if (_cell->getVelocity().x != 0.0f)
	{
		int direction = _cell->getVelocity().x > 0.0f ? 1 : -1;
		if (_x + direction >= 0 && _x + direction < _cell->getWidth() && canSwap(_cells[_y+1][_x+direction]))
		{
			_cell->setVelocity(_cell->getVelocity() + glm::vec2(direction, 0.0f));
			_target = &(_cells[_y + 1][_x + direction]);
		}
	}
	if (_x - _random >= 0 && _x - _random < _cell->getWidth() && canSwap(_cells[_y + 1][_x - _random]))
		_target = &(_cells[_y + 1][_x - _random]);
	else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && canSwap(_cells[_y + 1][_x + _random]))
		_target = &(_cells[_y + 1][_x + _random]);

	if (targetFound() == true)
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(_random, 0.0f));
}

void WaterMovement::checkAdjacentCells()
{
	if (_cell->getVelocity().x != 0.0f)
	{
		int direction = _cell->getVelocity().x > 0.0f ? 1 : -1;
		for (int i = 1; i < 5; i++)
		{
			int x = _x + i * direction;
			if (x >= 0 && x < _cell->getWidth() && canSwap(_cells[_y][x]))
				_target = &(_cells[_y][x]);
			else
				break;
		}
	}
	if (targetFound() == true)
		return;

	for (int i = 1; i < 5; i++)
	{
		int x = _x + i * _random;
		//std::cout << "x: " << _x << " --> " << x << std::endl;
		if (x >= 0 && x < _cell->getWidth() && canSwap(_cells[_y][x]))
			_target = &(_cells[_y][x]);
		else
			break;
	}
	if (targetFound() == true)
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(_random, 0.0f));
}

void WaterMovement::updateVelocity()
{
	_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.2f));
}

void WaterMovement::releaseRemainingVelocity()
{
	float yVelocity = _cell->getVelocity().y;
	_cell->setVelocity(glm::vec2(yVelocity * _random / 1.0f, yVelocity / 1.0f));
	_cell->setMovementBehavior(new ParticleMovement(_cell, *this));
}

const bool WaterMovement::targetFound()
{
	return _target;
}

const bool WaterMovement::cellHasVelocity()
{
	return _cell->getVelocity() != glm::vec2(0.0f);
}

const bool WaterMovement::canSwap(Cell& cell)
{
	if (cell.getType() == CellType::Gazeous)
		return true;
	else if (cell.getType() == CellType::Solid)
		return false;
	else
		return (_cell->_density > cell._density);
}
