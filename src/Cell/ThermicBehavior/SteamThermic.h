
#pragma once

#include "IThermicBehavior.h"
#include "../Factory/CellFactory.h"

class IThermicBehavior;
class CellFactory;

class SteamThermic : public IThermicBehavior {
private:

public:
	SteamThermic(Cell* cell);
	~SteamThermic();

	void update();
};
