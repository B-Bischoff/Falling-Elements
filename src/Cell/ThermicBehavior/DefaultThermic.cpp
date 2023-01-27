#include "DefaultThermic.h"

DefaultThermic::DefaultThermic(Cell* cell)
	: IThermicBehavior(cell)
{
}

void DefaultThermic::update()
{
	updateTemperature();
}
