#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class FlameThermic : public IThermicBehavior {
private:

public:
	FlameThermic(Cell* cell);
	~FlameThermic();

	void update();
};
