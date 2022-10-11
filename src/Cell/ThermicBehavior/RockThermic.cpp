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
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureLavaCell(*_cell);
	}
}
