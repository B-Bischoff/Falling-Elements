#pragma once

#include "../Cell.h"

#include "../MovementBehavior/SandBehavior.h"
#include "../MovementBehavior/WaterBehavior.h"
#include "../MovementBehavior/StaticBehavior.h"
#include "../MovementBehavior/SmokeBehavior.h"

#include "../ThermicBehavior/IThermicBehavior.h"
#include "../ThermicBehavior/WaterThermic.h"
#include "../ThermicBehavior/LavaThermic.h"

struct Element {
	std::string name;
	int index;
	static void (CellFactory::*method)(Cell&);
};

class CellFactory {
private:

public:
	static void configureCell(Cell& cell, const int& index);

	static void configureSandCell(Cell& cell);
	static void configureWaterCell(Cell& cell);
	static void configureRockCell(Cell& cell);
	static void configureAirCell(Cell& cell);
	static void configureSmokeCell(Cell& cell);
	static void configureLavaCell(Cell& cell);
};
