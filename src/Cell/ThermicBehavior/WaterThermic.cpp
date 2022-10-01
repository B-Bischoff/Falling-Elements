#include "WaterThermic.h"

WaterThermic::WaterThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void WaterThermic::update()
{
	int y = _cell->getPosition().y;
	int x = _cell->getPosition().x;

	int count = 1;
	int total = _cell->_temperature;

	if (y > 0)
	{
		count++;
		total += _cells[y - 1][x]._temperature;
	}
	if (y < _cell->getHeight() - 1)
	{
		count++;
		total += _cells[y + 1][x]._temperature;
	}
	if (x > 0)
	{
		count++;
		total += _cells[y][x - 1]._temperature;
	}
	if (x < _cell->getWidth() - 1)
	{
		count++;
		total += _cells[y][x + 1]._temperature;
	}

	_cell->_temperature = total / count;

	if (_cell->_temperature > 100.0f)
	{
		float temperature = _cell->_temperature;
		CellFactory::configureSmokeCell(*_cell);
		_cell->_temperature = temperature;

	}
}
