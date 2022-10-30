#include "FlameThermic.h"

FlameThermic::FlameThermic(Cell* cell)
	: IThermicBehavior(cell), _cycleToLive(15)
{
}

void FlameThermic::update()
{
	updateTemperature();

	if (_cycleToLive <= 0)
	{
		CellFactory::setTemperatureOnNextConfig(_cell->_temperature, _cell->_nextTemperature);
		CellFactory::configureDioxygenCell(*_cell);
	}
	else
		_cycleToLive--;
}
