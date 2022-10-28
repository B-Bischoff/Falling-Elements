
#include "SteamThermic.h"

SteamThermic::SteamThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void SteamThermic::update()
{
	updateTemperature();

	if (_cell->_temperature < 95.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureWaterCell(*_cell);
	}
}
