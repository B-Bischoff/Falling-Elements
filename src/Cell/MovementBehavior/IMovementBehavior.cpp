#include "IMovementBehavior.h"
#include "../Cell.h"

IMovementBehavior::IMovementBehavior(Cell* cell)
	: _cell(cell), _cells(cell->getCells())
{
}

IMovementBehavior::~IMovementBehavior()
{

}

void IMovementBehavior::setCell(Cell* cell)
{
	_cell = cell;
}

Cell* IMovementBehavior::getCell(void) const
{
	return _cell;
}
