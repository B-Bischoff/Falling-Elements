#include "LavaThermic.h"

LavaThermic::LavaThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void LavaThermic::update()
{
	updateTemperature();

	if (_cell->_temperature < 200.0f)
	{
		double temperature = _cell->_temperature;
		double nextTemperature = _cell->_nextTemperature;
		
		CellFactory::configureRockCell(*_cell);
		_cell->_temperature = temperature;
		_cell->_nextTemperature = nextTemperature;
	}
}
