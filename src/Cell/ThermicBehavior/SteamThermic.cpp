
#include "SteamThermic.h"

SteamThermic::SteamThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void SteamThermic::update()
{
	updateTemperature();

	if (_cell->_temperature < 100.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::configureWaterCell(*_cell);
		_cell->_temperature = temperature;
		_cell->_nextTemperature = nextTemperature;
	}
}
