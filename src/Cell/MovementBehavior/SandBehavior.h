#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleBehavior.h"

class IMovementBehavior;

class SandBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	SandBehavior(Cell* cell);
	~SandBehavior();

	void update();

private:
	void checkBelowCell();
	void checkAdjacentBelowCells();
	void updateVelocity();
	void transmitVelocity();
	void transmitVelocityToCell(const int& x, const int& y, const glm::vec2& friction);
	const bool targetFound();
	const bool cellHasVelocity();
};
