#pragma once

#include <iostream>
#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class WaterThermic : public IThermicBehavior {
private:

public:
	WaterThermic(Cell* cell);
	~WaterThermic();

	void update();

};
