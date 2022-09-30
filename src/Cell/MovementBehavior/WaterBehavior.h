#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleBehavior.h"

class IMovementBehavior;

class WaterBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell *_target;

public:
	WaterBehavior(Cell* cell);
	~WaterBehavior();

	void update();

private:
	void checkBelowCells();
	void checkAdjacentBelowCells();
	void checkAdjacentCells();
	void updateVelocity();
	void releaseRemainingVelocity();
	const bool targetFound();
	const bool cellHasVelocity();
};
