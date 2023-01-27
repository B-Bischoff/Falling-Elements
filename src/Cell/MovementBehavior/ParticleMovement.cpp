#include "ParticleMovement.h"

ParticleMovement::ParticleMovement(Cell* cell, IMovementBehavior& originMovement)
	: IMovementBehavior(cell), _originBehavior(originMovement)
{}

void ParticleMovement::update()
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

	if (cellHasVelocity() == false)
		setOriginalBehavior();
}

void ParticleMovement::moveUpward()
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

void ParticleMovement::moveDownward()
{
	int x = _cell->getPosition().x;
	int y = _cell->getPosition().y;
	if (y < _cell->getHeight() - 1 && y + 1 >= 0 && _cell->getType() > _cells[y + 1][x].getType())
		_cell->swapCell(_cells[y + 1][x]);
}

void ParticleMovement::moveLeft()
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

void ParticleMovement::moveRight()
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

void ParticleMovement::setOriginalBehavior()
{
	_cell->setMovementBehavior(&_originBehavior);
	_cell->getMovementBehavior()->setCell(_cell);
	delete this;
}

const bool ParticleMovement::cellHasVelocity() const
{
	return _cell->getVelocity() != glm::vec2(0.0f);
}
