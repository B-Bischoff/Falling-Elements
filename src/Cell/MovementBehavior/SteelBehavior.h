#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class SteelBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	SteelBehavior(Cell* cell);
	~SteelBehavior();

	void update();

private:
};
