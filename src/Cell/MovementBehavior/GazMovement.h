#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleMovement.h"

class IMovementBehavior;

class GazMovement : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	GazMovement(Cell* cell);
	~GazMovement();

	void update();

private:
	void checkUpCell();
	void checkAdjacentUpCells();
	void checkAdjacentCells();
	const bool canSwap(const Cell& cell) const;
	const bool targetFound() const;
};

