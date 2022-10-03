#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class LavaThermic : public IThermicBehavior {
private:

public:
	LavaThermic(Cell* cell);
	~LavaThermic();

	void update();
};
