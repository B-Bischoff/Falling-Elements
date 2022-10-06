#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class RockThermic : public IThermicBehavior {
private:

public:
	RockThermic(Cell* cell);
	~RockThermic();

	void update();
};
