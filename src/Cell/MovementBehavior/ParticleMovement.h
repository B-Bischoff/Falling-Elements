#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class ParticleMovement : public IMovementBehavior {
private:
	IMovementBehavior& _originBehavior;

	void moveUpward();
	void moveDownward();
	void moveLeft();
	void moveRight();
	void setOriginalBehavior();

	const bool cellHasVelocity() const;

public:
	ParticleMovement(Cell* cell, IMovementBehavior& originBehavior);
	~ParticleMovement() {};
	
	void update();
};

