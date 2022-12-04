#include "ParticleBehavior.h"

ParticleBehavior::ParticleBehavior(Cell* cell, IMovementBehavior& originBehavior)
	: IMovementBehavior(cell), _originBehavior(originBehavior)
{}

void ParticleBehavior::update()
{
	if (_cell->getVelocity().y > 0.0f)
		moveUpward();
	else
		moveDownward();

	if (_cell->getVelocity().x > 0.0f)
		moveLeft();
	else if (_cell->getVelocity().x < 0.0f)
		moveRight();

	if (_cell->getVelocity().y < 0.0f)
		_cell->setVelocity(glm::vec2(0.0f, _cell->getVelocity().x));

	if (_cell->getVelocity() == glm::vec2(0.0f)) // If no velocity left, set originalBehavior on the cell
		setOriginalBehavior();
}

void ParticleBehavior::moveUpward()
{
	int x = _cell->getPosition().x;
	int y = _cell->getPosition().y;
	if (_cell->getVelocity().y >= 1.0f && y - 1 >= 0 && _cell->getType() > _cells[y - 1][x].getType())
	{
		_cell->swapCell(_cells[y - 1][x]);
		_cell->setVelocity(_cell->getVelocity() - glm::vec2(0.0f, 1.0f));

		if (_cell->getVelocity().y < 0.0f)
			_cell->setVelocity(glm::vec2(_cell->getVelocity().x, 0.0f));
	}
	else
		_cell->setVelocity(glm::vec2(_cell->getVelocity().x, 0.0f));
}

void ParticleBehavior::moveDownward()
{
	int x = _cell->getPosition().x;
	int y = _cell->getPosition().y;
	if (y < _cell->getHeight() - 1 && y + 1 >= 0 && _cell->getType() > _cells[y + 1][x].getType())
		_cell->swapCell(_cells[y + 1][x]);
}

void ParticleBehavior::moveLeft()
{
	int x = _cell->getPosition().x;
	int y = _cell->getPosition().y;
	if (_cell->getVelocity().x <= -1.0f && x - 1 >= 0 && _cell->getType() > _cells[y][x - 1].getType())
	{
		_cell->swapCell(_cells[y][x - 1]);
		_cell->setVelocity(_cell->getVelocity() + glm::vec2(1.0f, 0.0f));

		if (_cell->getVelocity().x > 0.0f)
			_cell->setVelocity(glm::vec2(0.0f, _cell->getVelocity().y));
	}
	else
		_cell->setVelocity(glm::vec2(0.0f, _cell->getVelocity().y));

}

void ParticleBehavior::moveRight()
{
	int x = _cell->getPosition().x;
	int y = _cell->getPosition().y;
	if (_cell->getVelocity().x >= 1.0f && x + 1 < _cell->getWidth() && _cell->getType() > _cells[y][x + 1].getType())
	{
		_cell->swapCell(_cells[y][x + 1]);
		_cell->setVelocity(_cell->getVelocity() - glm::vec2(1.0f, 0.0f));

		// Clamp
		if (_cell->getVelocity().x < 0.0f)
			_cell->setVelocity(glm::vec2(0.0f, _cell->getVelocity().y));
	}
	else
		_cell->setVelocity(glm::vec2(0.0f, _cell->getVelocity().y));
}

void ParticleBehavior::setOriginalBehavior()
{
	_cell->setMovementBehavior(&_originBehavior);
	_cell->getMovementBehavior()->setCell(_cell);
	delete this;
}
