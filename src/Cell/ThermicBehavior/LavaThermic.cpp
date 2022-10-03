#include "LavaThermic.h"

LavaThermic::LavaThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void LavaThermic::update()
{
	updateTemperature();

	if (_cell->_temperature < 200.0f)
	{
		float temperature = _cell->_temperature;
		CellFactory::configureRockCell(*_cell);
		_cell->_temperature = temperature;
	}
}
