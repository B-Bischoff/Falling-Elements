#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class StaticMovement : public IMovementBehavior {
private:

public:
	StaticMovement(Cell* cell);
	~StaticMovement();

	void update();
};
