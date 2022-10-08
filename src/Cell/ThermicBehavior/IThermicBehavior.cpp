#include "IThermicBehavior.h"

IThermicBehavior::IThermicBehavior(Cell* cell)
	: _cell(cell), _cells(cell->getCells())
{
}

IThermicBehavior::~IThermicBehavior()
{
}

void IThermicBehavior::update()
{
	updateTemperature();
}

void IThermicBehavior::updateTemperature()
{
	int y = _cell->getPosition().y;
	int x = _cell->getPosition().x;

	//_cell->_nextTemperature = _cell->_temperature;
	const double VALUE = _cell->_temperature * 0.015f;

	if (y > 0)
	{
		Cell& target = _cells[y - 1][x];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (y < _cell->getHeight() - 1)
	{
		Cell& target = _cells[y + 1][x];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (x > 0)
	{
		Cell& target = _cells[y][x - 1];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (x < _cell->getWidth() - 1)
	{
		Cell& target = _cells[y][x + 1];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (y > 0 && x < _cell->getWidth() - 1)
	{
		Cell& target = _cells[y - 1][x + 1];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (y < _cell->getHeight() - 1 && x < _cell->getWidth() - 1)
	{
		Cell& target = _cells[y + 1][x + 1];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (y > 0 && x > 0)
	{
		Cell& target = _cells[y - 1][x - 1];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
	if (y < _cell->getHeight() - 1 && x > 0)
	{
		Cell& target = _cells[y + 1][x - 1];
		updateTarget(target, VALUE * target._thermalConductivity);
	}
}

void IThermicBehavior::updateTarget(Cell& target, const double& value)
{
	target._nextTemperature += value;
	_cell->_nextTemperature -= value;
}

void IThermicBehavior::updateTemperature2()
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
	if (y > 0 && x < _cell->getWidth() - 1)
	{
		count++;
		total += _cells[y - 1][x + 1]._temperature;
	}
	if (y < _cell->getHeight() - 1 && x < _cell->getWidth() - 1)
	{
		count++;
		total += _cells[y + 1][x + 1]._temperature;
	}
	if (y > 0 && x > 0)
	{
		count++;
		total += _cells[y - 1][x - 1]._temperature;
	}
	if (y < _cell->getHeight() - 1 && x > 0)
	{
		count++;
		total += _cells[y + 1][x - 1]._temperature;
	}

	_cell->_nextTemperature = total / count;
}

void IThermicBehavior::setCell(Cell* cell)
{
	_cell = cell;
}

Cell* IThermicBehavior::getCell(void) const
{
	return _cell;
}
