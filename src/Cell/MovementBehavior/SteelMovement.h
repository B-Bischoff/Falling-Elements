#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class SteelMovement : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	SteelMovement(Cell* cell);
	~SteelMovement();

	void update();

private:
};
