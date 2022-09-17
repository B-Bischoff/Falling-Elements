#pragma once

#include "../Cell.h"
#include "../MovementBehavior/SandBehavior.h"
#include "../MovementBehavior/WaterBehavior.h"
#include "../MovementBehavior/StaticBehavior.h"


class CellFactory {
private:

public:
	static void configureSandCell(Cell& cell);
	static void configureWaterCell(Cell& cell);
	static void configureRockCell(Cell& cell);
};
