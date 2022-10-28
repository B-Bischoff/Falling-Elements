#include "WaterThermic.h"

WaterThermic::WaterThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void WaterThermic::update()
{
	updateTemperature();

	if (_cell->_temperature >= 105.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureSmokeCell(*_cell);
	}
    else if (_cell->_temperature <= 0.0f)
    {
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;

		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureIceCell(*_cell);
    }
}
