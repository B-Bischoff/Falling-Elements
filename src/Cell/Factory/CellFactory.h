#pragma once

#include "../Cell.h"

#include "../MovementBehavior/SandMovement.h"
#include "../MovementBehavior/WaterMovement.h"
#include "../MovementBehavior/StaticMovement.h"
#include "../MovementBehavior/SmokeMovement.h"
#include "../MovementBehavior/RockMovement.h"
#include "../MovementBehavior/GazMovement.h"
#include "../MovementBehavior/SteelMovement.h"

#include "../ThermicBehavior/IThermicBehavior.h"
#include "../ThermicBehavior/DefaultThermic.h"
#include "../ThermicBehavior/WaterThermic.h"
#include "../ThermicBehavior/LavaThermic.h"
#include "../ThermicBehavior/RockThermic.h"
#include "../ThermicBehavior/SteamThermic.h"
#include "../ThermicBehavior/FlameThermic.h"
#include "../ThermicBehavior/FlammableThermic.h"
#include "../ThermicBehavior/IceThermic.h"

class CellFactory {
private:
	static bool _setSpecificTemperature;
	static double _temperature, _nextTemperature;

	static void setTemperature(Cell& cell, const double& temperature, const double& nextTemperature);
	static void deleteBehaviors(Cell& cell);

public:
	static void configureCell(Cell& cell, const int& index);

	static void setTemperatureOnNextConfig(const double& temperature, const double& nextTemperature);

	static void configureSandCell(Cell& cell);
	static void configureWaterCell(Cell& cell);
	static void configureRockCell(Cell& cell);
	static void configureAirCell(Cell& cell);
	static void configureSmokeCell(Cell& cell);
	static void configureLavaCell(Cell& cell);
	static void configureOilCell(Cell& cell);
	static void configureFlameCell(Cell& cell);
    static void configureIceCell(Cell& cell);
	static void configureSteelCell(Cell& cell);
	static void configureDioxygenCell(Cell& cell);
};
