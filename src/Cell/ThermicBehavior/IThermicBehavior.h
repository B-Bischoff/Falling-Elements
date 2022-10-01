#pragma once

#include "../Cell.h"

class Cell;

class IThermicBehavior {
protected:
	Cell** _cells;
	Cell* _cell;

public:
	IThermicBehavior(Cell* cell);
	~IThermicBehavior();
	virtual void update();

	void setCell(Cell* cell);
	Cell* getCell(void) const;

};
