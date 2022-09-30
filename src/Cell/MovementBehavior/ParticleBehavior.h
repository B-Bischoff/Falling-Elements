#pragma once

#include <iostream>
#include "IMovementBehavior.h"

class IMovementBehavior;

class ParticleBehavior : public IMovementBehavior {
private:
	IMovementBehavior& _originBehavior;

public:
	ParticleBehavior(Cell* cell, IMovementBehavior& originBehavior);
	~ParticleBehavior() {};
	
	void update();
};

