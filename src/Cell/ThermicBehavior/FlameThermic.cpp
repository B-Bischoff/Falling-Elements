#include "FlameThermic.h"

FlameThermic::FlameThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void FlameThermic::update()
{
	updateTemperature();

	/*if (_cell->_temperature >= 200.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureLavaCell(*_cell);
	}*/

	if (_cell->_temperature <= 500.0)
	{
		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureAirCell(*_cell);
	}
}
