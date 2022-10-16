#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class FlammableThermic : public IThermicBehavior {
private:

public:
	FlammableThermic(Cell* cell);
	~FlammableThermic();

	void update();
};
