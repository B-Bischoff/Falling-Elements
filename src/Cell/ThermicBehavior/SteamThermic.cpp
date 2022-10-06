
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
		float temperature = _cell->_temperature;
		CellFactory::configureWaterCell(*_cell);
		_cell->_temperature = temperature;
	}
}
