#include "WaterThermic.h"

WaterThermic::WaterThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void WaterThermic::update()
{
	updateTemperature();

	if (_cell->_temperature >= 100.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::configureSmokeCell(*_cell);
		_cell->_temperature = temperature;
		_cell->_nextTemperature = nextTemperature;
	}
}
