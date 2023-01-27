#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleMovement.h"

class IMovementBehavior;

class WaterMovement : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell *_target;

public:
	WaterMovement(Cell* cell);
	~WaterMovement();

	void update();

private:
	void checkBelowCells();
	void checkAdjacentBelowCells();
	void checkAdjacentCells();
	void updateVelocity();
	void releaseRemainingVelocity();
	const bool targetFound();
	const bool cellHasVelocity();
	const bool canSwap(Cell& cell);
};
