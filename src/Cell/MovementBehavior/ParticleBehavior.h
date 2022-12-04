#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class ParticleBehavior : public IMovementBehavior {
private:
	IMovementBehavior& _originBehavior;

	void moveUpward();
	void moveDownward();
	void moveLeft();
	void moveRight();
	void setOriginalBehavior();

public:
	ParticleBehavior(Cell* cell, IMovementBehavior& originBehavior);
	~ParticleBehavior() {};
	
	void update();
};

