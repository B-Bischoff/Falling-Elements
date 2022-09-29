#include "IMovementBehavior.h"

IMovementBehavior::IMovementBehavior(Cell* cell)
	: _cell(cell), _cells(cell->getCells()), hasMoved(false)
{
}

IMovementBehavior::~IMovementBehavior()
{

}

void IMovementBehavior::update()
{
	_cell->setVelocity(glm::vec2(0.0f));
}

void IMovementBehavior::setCell(Cell* cell)
{
	_cell = cell;
}

Cell* IMovementBehavior::getCell(void) const
{
	return _cell;
}
