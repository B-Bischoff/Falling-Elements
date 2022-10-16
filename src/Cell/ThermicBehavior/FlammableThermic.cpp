#include "FlammableThermic.h"

FlammableThermic::FlammableThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void FlammableThermic::update()
{
	updateTemperature();

	if (_cell->_temperature >= 200.0)
	{
		CellFactory::configureFlameCell(*_cell);
	}
}
