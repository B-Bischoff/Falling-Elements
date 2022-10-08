#pragma once

#include "../Cell.h"

class Cell;

class IThermicBehavior {
protected:
	Cell** _cells;
	Cell* _cell;

	void updateTemperature();
	void updateTemperature2();
	void updateTarget(Cell& target, const double& value);

public:
	IThermicBehavior(Cell* cell);
	~IThermicBehavior();
	virtual void update();

	void setCell(Cell* cell);
	Cell* getCell(void) const;

};
