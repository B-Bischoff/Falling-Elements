#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "../Factory/CellFactory.h"

class Cell;

class SmokeBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;
	int _test = 0;

public:
	SmokeBehavior(Cell* cell);
	~SmokeBehavior();

	void update();
	void checkUpCell();
	void checkAdjacentUpCells();
	const bool targetFound();

};
