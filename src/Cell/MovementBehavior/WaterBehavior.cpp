#include "WaterBehavior.h"

WaterBehavior::WaterBehavior(Cell* cell)
	: IMovementBehavior(cell)
{

}

void WaterBehavior::update()
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

void WaterBehavior::checkBelowCells()
{
	for (int i = 0; i <= _cell->getVelocity().y; i++)
	{
		if ((_y + i + 1) < _cell->getHeight() && _cells[_y + i + 1][_x].getType() < CellType::Liquid)
			_target = &(_cells[_y + i + 1][_x]);
		else
			break;
	}
}

void WaterBehavior::checkAdjacentBelowCells()
{
	if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y + 1][_x - _random].getType() < CellType::Liquid)
		_target = &(_cells[_y + 1][_x - _random]);
	else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y + 1][_x + _random].getType() < CellType::Liquid)
		_target = &(_cells[_y + 1][_x + _random]);
}

void WaterBehavior::checkAdjacentCells()
{
	/*
	for (int i = 0; i < 5; i++)
	{
		if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y][_x + _random].getType() < CellType::Liquid)
			_target = &(_cells[_y][_x + _random]);
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y][_x - _random].getType() < CellType::Liquid)
			_target = &(_cells[_y][_x - _random]);
	}*/

	for (int i = 1; i < 5; i++)
	{
		int x = _x + i * _random;
		//std::cout << "x: " << _x << " --> " << x << std::endl;
		if (x >= 0 && x < _cell->getWidth() && _cells[_y][x].getType() < CellType::Liquid)
			_target = &(_cells[_y][x]);
		else
			break;
	}
	for (int i = 1; i < 5; i++)
	{
		int x = _x + i * -_random;
		if (x >= 0 && x < _cell->getWidth() && _cells[_y][x].getType() < CellType::Liquid)
			_target = &(_cells[_y][x]);
		else
			break;
	}
}

void WaterBehavior::updateVelocity()
{
	_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.2f));
}

void WaterBehavior::releaseRemainingVelocity()
{
	float yVelocity = _cell->getVelocity().y;
	_cell->setVelocity(glm::vec2(yVelocity * _random / 1.0f, yVelocity / 1.0f));
	_cell->setMovementBehavior(new ParticleBehavior(_cell, *this));
}

const bool WaterBehavior::targetFound()
{
	return _target;
}

const bool WaterBehavior::cellHasVelocity()
{
	return _cell->getVelocity() != glm::vec2(0.0f);
}
