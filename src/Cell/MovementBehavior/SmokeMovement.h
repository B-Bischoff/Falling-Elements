#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "../Factory/CellFactory.h"

class Cell;

class SmokeMovement : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;
	int _test = 0;

	void checkUpCell();
	void checkAdjacentUpCells();
	void checkAdjacentCells();
	const bool targetFound();
	const bool canSwap(const Cell& cell) const;

public:
	SmokeMovement(Cell* cell);
	~SmokeMovement();

	void update();
};
