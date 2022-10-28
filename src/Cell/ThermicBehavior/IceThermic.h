#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class IceThermic : public IThermicBehavior {
private:

public:
	IceThermic(Cell* cell);
	~IceThermic();

	void update();
};

