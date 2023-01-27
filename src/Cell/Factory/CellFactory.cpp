#include "CellFactory.h"

bool CellFactory::_setSpecificTemperature = false;
double CellFactory::_temperature = 0;
double CellFactory::_nextTemperature = 0;

void CellFactory::configureCell(Cell& cell, const int& index)
{
	switch (index)
	{
	case 0: configureAirCell(cell); break;
	case 1: configureSandCell(cell); break;
	case 2: configureWaterCell(cell); break;
	case 3: configureRockCell(cell); break;
	case 4: configureSmokeCell(cell); break;
	case 5: configureLavaCell(cell); break;
	case 6: configureOilCell(cell); break;
	case 7: configureFlameCell(cell); break;
	case 8: configureIceCell(cell); break;
	case 9: configureSteelCell(cell); break;
	case 10:configureDioxygenCell(cell); break;

	default: break;
	}
}

void CellFactory::setTemperatureOnNextConfig(const double& temperature, const double& nextTemperature)
{
	_setSpecificTemperature = true;
	_temperature = temperature;
	_nextTemperature = nextTemperature;
}

void CellFactory::configureSandCell(Cell& cell)
{
	float r = (100 - rand() % 6) / 100.0f;
	float g = (85 - rand() % 11) / 100.0f;
	float b = (65 - rand() % 11) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Solid);

	setTemperature(cell, 50.0, 50.0);
	cell.setVelocity(glm::vec2(0.0f));

	cell._temperature = 50;
	cell._nextTemperature = 50;
	cell._thermalConductivity = 1.5;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new SandMovement(&cell));
	cell.SetThermicBehavior(new IThermicBehavior(&cell));
}

void CellFactory::configureWaterCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.6f, 1.0f));
	cell.setType(CellType::Liquid);
	setTemperature(cell, 10.0, 10.0);
	cell.setVelocity(glm::vec2(0.0f));
	cell._thermalConductivity = 1.0;
	cell._density = 1;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new WaterMovement(&cell));
	cell.SetThermicBehavior(new WaterThermic(&cell));
}

void CellFactory::configureRockCell(Cell& cell)
{
	float random = rand() % 7;
	float r = (25 - random) / 100.0f;
	float g = (25 - random) / 100.0f;
	float b = (25 - random) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Solid);
	setTemperature(cell, 0.0, 0.0);
	cell.setVelocity(glm::vec2(0.0f));
	cell._thermalConductivity = 1.4;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new RockMovement(&cell));
	cell.SetThermicBehavior(new RockThermic(&cell));
}

void CellFactory::configureAirCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.25f, 0.65f));
	cell.setType(CellType::Gazeous);
	setTemperature(cell, 20.0, 20.0);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 2;
	cell._thermalConductivity = 0.4;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new GazMovement(&cell));
	cell.SetThermicBehavior(new IThermicBehavior(&cell));
}

void CellFactory::configureSmokeCell(Cell& cell)
{
	const float random = (80 - rand() % 15) / 100.0f;
	float r = random;
	float g = random;
	float b = random;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Gazeous);
	cell.setVelocity(glm::vec2(0.0f));
	setTemperature(cell, 20.0, 20.0);
	cell._density = 1;
	cell._thermalConductivity = 0.7;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new SmokeMovement(&cell));
	cell.SetThermicBehavior(new SteamThermic(&cell));
}

void CellFactory::configureLavaCell(Cell& cell)
{
	float r = (100 - rand() % 16) / 100.0f;
	float g = (30 - rand() % 21) / 100.0f;
	float b = 0.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Liquid);
	setTemperature(cell, 1500.0, 1500.0);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 1;
	cell._thermalConductivity = 0.4;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new WaterMovement(&cell));
	cell.SetThermicBehavior(new LavaThermic(&cell));
}

void CellFactory::configureOilCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.06f));
	cell.setType(CellType::Liquid);
	setTemperature(cell, 50.0, 5.0);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 0.7;
	cell._thermalConductivity = 1.0;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new WaterMovement(&cell));
	cell.SetThermicBehavior(new FlammableThermic(&cell));
}

void CellFactory::configureFlameCell(Cell& cell)
{
	float r = (100 - rand() % 16) / 100.0f;
	float g = (50 - rand() % 21) / 100.0f;
	float b = 0.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Gazeous);
	setTemperature(cell, 1000, 1000);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 1;
	cell._thermalConductivity = 1.0;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new SmokeMovement(&cell));
	cell.SetThermicBehavior(new FlameThermic(&cell));
}

void CellFactory::configureIceCell(Cell& cell)
{
	float r = 0.2f;
	float g = (50 - rand() % 11) / 100.0f;
	float b = (100 - rand() % 16) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Solid);
	setTemperature(cell, -50, -50);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 1;
	cell._thermalConductivity = 1.0;
	cell._friction = 4;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new RockMovement(&cell));
	cell.SetThermicBehavior(new IceThermic(&cell));
}

void CellFactory::configureSteelCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.5f));
	cell.setType(CellType::Solid);
	setTemperature(cell, 20, 20);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 1;
	cell._thermalConductivity = 3.0f;
	cell._friction = 1;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new SteelMovement(&cell));
	cell.SetThermicBehavior(new IThermicBehavior(&cell));
}

void CellFactory::configureDioxygenCell(Cell& cell)
{
	const float random = (20.0f - rand() % 11) / 100.0f;

	cell.setColor(glm::vec3(random));
	cell.setType(CellType::Gazeous);
	setTemperature(cell, 50.0, 50.0);
	cell.setVelocity(glm::vec2(0.0f));
	cell._density = 2.5;
	cell._thermalConductivity = 0.2;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new GazMovement(&cell));
	cell.SetThermicBehavior(new IThermicBehavior(&cell));
}

void CellFactory::setTemperature(Cell& cell, const double& temperature, const double& nextTemperature)
{
	if (_setSpecificTemperature)
	{
		cell._temperature = _temperature;
		cell._nextTemperature = _nextTemperature;
	}
	else
	{
		cell._temperature = temperature;
		cell._nextTemperature = nextTemperature;
	}
	_setSpecificTemperature = false;
}

void CellFactory::deleteBehaviors(Cell& cell)
{
	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();
	if (cell.getThermicBehavior() != nullptr)
		delete cell.getThermicBehavior();
}
