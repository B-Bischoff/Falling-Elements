#include "RockThermic.h"

RockThermic::RockThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void RockThermic::update()
{
	updateTemperature();

	if (_cell->_temperature >= 200.0f)
	{
		float temperature = _cell->_temperature;
		CellFactory::configureLavaCell(*_cell);
		_cell->_temperature = temperature;
	}
}
