#include "RockMovement.h"

RockMovement::RockMovement(Cell* cell)
	: IMovementBehavior(cell)
{

}

void RockMovement::update()
{
	_target = nullptr;
	_x = _cell->getPosition().x;
	_y = _cell->getPosition().y;

	if (_y < _cell->getHeight() - 1)
	{
		_random = (rand() % 2) * 2 - 1; // '_random' can be -1 or 1

		checkBelowCell();
		if (targetFound() == false && cellHasVelocity() == true)
		{
			checkAdjacentBelowCells();
		}

		if (targetFound() == true)
		{
			updateVelocity();
			_cell->swapCell(*_target);
		}
	}

	if (targetFound() == false && cellHasVelocity() == true)
	{
		transmitVelocity();
		_cell->setMovementBehavior(new ParticleMovement(_cell, *this));
	}
}

void RockMovement::checkBelowCell()
{
	for (int i = 0; i <= _cell->getVelocity().y; i++)
	{
		if ((_y + i + 1) < _cell->getHeight() && _cells[_y + i + 1][_x].getType() < CellType::Solid)
			_target = &(_cells[_y + i + 1][_x]);
		else
			break;
	}
}

void RockMovement::checkAdjacentBelowCells()
{
	if (_cell->getVelocity().x != 0.0f)
	{
		int direction = _cell->getVelocity().x > 0.0f ? 1 : -1;
		if (_x + direction >= 0 && _x + direction < _cell->getWidth() && _cells[_y + 1][_x + direction].getType() < CellType::Solid)
		{
			_target = &(_cells[_y + 1][_x + direction]);
			_cell->setVelocity(_cell->getVelocity() + glm::vec2(direction / 2.0f, 0.0f));
			return;
		}
	}

	if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y + 1][_x - _random].getType() < CellType::Solid)
		_target = &(_cells[_y + 1][_x - _random]);
	else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y + 1][_x + _random].getType() < CellType::Solid)
		_target = &(_cells[_y + 1][_x + _random]);

	if (targetFound() == true)
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(_random / 2.0f, 0.0f));
}

void RockMovement::updateVelocity()
{
	if (_target->getType() == CellType::Gazeous) // Accelerate in free falling
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.20f));
	else if (_target->getType() == CellType::Liquid && _cell->getVelocity().y > 0.8f) // Get slow done by liquid
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, -0.8f));
}

void RockMovement::transmitVelocity()
{
	const float X_FRI = 1.0f;
	const float Y_FRI = 1.0f;
	const glm::vec2 friction(X_FRI, Y_FRI);

	const float CELLfriction = _cell->_friction; // To add in Cell class

	const glm::vec2& velocity = _cell->getVelocity();
	float xVel = velocity.x + velocity.y * CELLfriction;
		if (xVel > 1.0f || xVel < -1.0f)
		xVel = rand() % (int)xVel * _random;

	_cell->setVelocity(glm::vec2(xVel, 0.0f));

	if (_y + 1 < _cell->getHeight())
	{
		transmitVelocityToCell(_x, _y+1, friction);
		transmitVelocityToCell(_x-1, _y+1, friction);
		transmitVelocityToCell(_x+1, _y+1, friction);
	}
//
//	float yVel = _cell->getVelocity().y;
//	float xVel = _cell->getVelocity().x;
//	_cell->setVelocity(glm::vec2(xVel * (1.0f - X_FRI), yVel * (1.0f - Y_FRI)));
	//std::cout << "x: " << _cell->getVelocity().x << " y: " << _cell->getVelocity().y << std::endl;

}

void RockMovement::transmitVelocityToCell(const int& x, const int& y, const glm::vec2& friction)
{
	if (x >= _cell->getWidth() || x < 0)
		return;
	if (y >= _cell->getHeight() || y < 0)
		return;
	if (_cells[y][x].getType() != CellType::Solid)
		return;

	glm::vec2 velocity = _cell->getVelocity();
	glm::vec2 targetVelocity = _cells[y][x].getVelocity();
	glm::vec2 finalVelocity = targetVelocity + glm::vec2(velocity.x * friction.x, velocity.y * friction.y);
	_cells[y][x].setVelocity(finalVelocity);
}

const bool RockMovement::targetFound()
{
	return _target;
}

const bool RockMovement::cellHasVelocity()
{
	return _cell->getVelocity() != glm::vec2(0.0f);
}
