#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class DefaultThermic : public IThermicBehavior {
private:

public:
	DefaultThermic(Cell* cell);
	~DefaultThermic();

	void update();
};
