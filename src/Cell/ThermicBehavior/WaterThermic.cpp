#include "WaterThermic.h"

WaterThermic::WaterThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void WaterThermic::update()
{
	updateTemperature();

	if (_cell->_temperature > 100.0f)
	{
		float temperature = _cell->_temperature;
		CellFactory::configureSmokeCell(*_cell);
		_cell->_temperature = temperature;
	}
}
