#include "IceThermic.h"

IceThermic::IceThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void IceThermic::update()
{
	updateTemperature();

	if (_cell->_temperature > 0.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureWaterCell(*_cell);
	}
}

