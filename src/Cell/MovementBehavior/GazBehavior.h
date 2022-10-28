#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleBehavior.h"

class IMovementBehavior;

class GazBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	GazBehavior(Cell* cell);
	~GazBehavior();

	void update();

private:
	void checkUpCell();
	void checkAdjacentUpCells();
	void checkAdjacentCells();
	const bool canSwap(const Cell& cell) const;
	const bool targetFound() const;
};
