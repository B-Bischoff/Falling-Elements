#include "RockBehavior.h"

RockBehavior::RockBehavior(Cell* cell)
	: IMovementBehavior(cell)
{

}

void RockBehavior::update()
{
	_target = nullptr;
	_x = _cell->getPosition().x;
	_y = _cell->getPosition().y;

	if (_y < _cell->getHeight() - 1)
	{
		_random = (rand() % 2) * 2 - 1; // 'random' can be -1 or 1

		checkBelowCell();
		if (targetFound() == false && cellHasVelocity() == true)
			CheckAdjacentBelowCells();
		
		if (targetFound() == false && cellHasVelocity() == true) 
			transmitVelocity();
		else if (targetFound() == true)
		{
			updateVelocity();
			_cell->swapCell(*_target);
		}
	}

	if (targetFound() == false && cellHasVelocity() == true)
		_cell->setMovementBehavior(new ParticleBehavior(_cell, *this));
}

void RockBehavior::checkBelowCell()
{
	for (int i = 0; i <= _cell->getVelocity().y; i++)
	{
		if ((_y + i + 1) < _cell->getHeight() && _cells[_y + i + 1][_x].getType() < CellType::Solid)
			_target = &(_cells[_y + i + 1][_x]);
		else
			break;
	}
}

void RockBehavior::CheckAdjacentBelowCells()
{
	if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y + 1][_x - _random].getType() < CellType::Solid)
		_target = &(_cells[_y + 1][_x - _random]);
	else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y + 1][_x + _random].getType() < CellType::Solid)
		_target = &(_cells[_y + 1][_x + _random]);
}

void RockBehavior::updateVelocity()
{
	if (_target->getType() == CellType::Gazeous) // Accelerate in free falling
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.20f));
	else if (_target->getType() == CellType::Liquid && _cell->getVelocity().y > 0.8f) // Get slow done by liquid
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, -0.8f));
}

void RockBehavior::transmitVelocity()
{
	const float X_FRI = 0.40f;
	const float Y_FRI = 0.45f;
	const glm::vec2 friction(X_FRI, Y_FRI);

	if (_cells[_y + 1][_x].getType() == CellType::Solid && _cells[_y+1][_x].getVelocity()==glm::vec2(0.0f))
		transmitVelocityToCell(_x, _y+1, friction);
	if (_cells[_y + 1][_x - 1].getType() == CellType::Solid && _cells[_y+1][_x-1].getVelocity()==glm::vec2(0.0f))
		transmitVelocityToCell(_x-1, _y+1, friction);
	if (_cells[_y + 1][_x + 1].getType() == CellType::Solid && _cells[_y+1][_x+1].getVelocity()==glm::vec2(0.0f))
		transmitVelocityToCell(_x+1, _y+1, friction);

	float yVel = _cell->getVelocity().y;
	_cell->setVelocity(glm::vec2(yVel * Y_FRI * _random, yVel * X_FRI));
}

void RockBehavior::transmitVelocityToCell(const int& x, const int& y, const glm::vec2& friction)
{
	if (x >= _cell->getWidth() || x < 0) 
		return;
	if (y >= _cell->getHeight() || y < 0)
		return;

	glm::vec2 velocity = _cell->getVelocity();
	glm::vec2 targetVelocity = _cells[y][x].getVelocity();
	glm::vec2 finalVelocity = targetVelocity + glm::vec2(velocity.y * friction.x, velocity.y * friction.y);
	_cells[y][x].setVelocity(finalVelocity);
}

const bool RockBehavior::targetFound()
{
	return _target;
}

const bool RockBehavior::cellHasVelocity()
{
	return _cell->getVelocity() != glm::vec2(0.0f);
}
