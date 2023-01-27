#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleMovement.h"

class IMovementBehavior;
class SandMovement : public IMovementBehavior { private: int _x, _y; int _random; Cell* _target; public:
	SandMovement(Cell* cell);
	~SandMovement();

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
