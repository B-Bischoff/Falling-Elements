#pragma once

#include "../Cell.h"

class Cell;

class IMovementBehavior {
protected:
	Cell** _cells;
	Cell* _cell;

public:
	IMovementBehavior(Cell* cell);
	~IMovementBehavior();
	virtual void update();

	void setCell(Cell* cell);
	Cell* getCell(void) const;

	bool hasMoved;
};
