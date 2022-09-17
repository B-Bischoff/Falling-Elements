#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class StaticBehavior : public IMovementBehavior {
private:

public:
	StaticBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~StaticBehavior() {};

	void update()
	{

	}
};
