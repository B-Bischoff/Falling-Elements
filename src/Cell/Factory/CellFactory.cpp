#include "CellFactory.h"

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
	
	default: break;
	}
}

void CellFactory::configureSandCell(Cell& cell)
{
	float r = (100 - rand() % 6) / 100.0f;
	float g = (85 - rand() % 11) / 100.0f;
	float b = (65 - rand() % 11) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Solid);
	cell._temperature = 50;
	cell._nextTemperature = 50;
	cell._thermalConductivity = 1.5;

	deleteBehaviors(cell);
	
	cell.setMovementBehavior(new SandBehavior(&cell));
	cell.SetThermicBehavior(new IThermicBehavior(&cell));
}

void CellFactory::configureWaterCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.6f, 1.0f));
	cell.setType(CellType::Liquid);
	cell._temperature = 10;
	cell._nextTemperature = 10;
	cell._thermalConductivity = 0.7;

	deleteBehaviors(cell);
	
	cell.setMovementBehavior(new WaterBehavior(&cell));
	cell.SetThermicBehavior(new WaterThermic(&cell));
}

void CellFactory::configureRockCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.2f, 0.2f));
	cell.setType(CellType::Solid);
	cell._temperature = 0;
	cell._nextTemperature = 0;
	cell._thermalConductivity = 1.7;
	
	deleteBehaviors(cell);

	cell.setMovementBehavior(new StaticBehavior(&cell));
	cell.SetThermicBehavior(new RockThermic(&cell));
}

void CellFactory::configureAirCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.0f, 0.2f));
	cell.setType(CellType::Gazeous);
	cell._temperature = 20;
	cell._nextTemperature = 20;
	cell._density = 2;
	cell._thermalConductivity = 0.2;
	
	deleteBehaviors(cell);

	cell.setMovementBehavior(new IMovementBehavior(&cell));
	cell.SetThermicBehavior(new IThermicBehavior(&cell));
}

void CellFactory::configureSmokeCell(Cell& cell)
{
	float r = (80 - rand() % 6) / 100.0f;
	float g = (80 - rand() % 6) / 100.0f;
	float b = (80 - rand() % 6) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Gazeous);
	cell._temperature = 20;
	cell._nextTemperature = 20;
	cell._density = 1;
	cell._thermalConductivity = 0.7;
	
	deleteBehaviors(cell);

	cell.setMovementBehavior(new SmokeBehavior(&cell));
	cell.SetThermicBehavior(new SteamThermic(&cell));
}

void CellFactory::configureLavaCell(Cell& cell)
{
	float r = (100 - rand() % 16) / 100.0f;
	float g = (30 - rand() % 21) / 100.0f;
	float b = 0.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Liquid);
	cell._temperature = 1000;
	cell._nextTemperature = 1000;
	cell._density = 1;
	cell._thermalConductivity = 1.0;

	deleteBehaviors(cell);

	cell.setMovementBehavior(new WaterBehavior(&cell));
	cell.SetThermicBehavior(new LavaThermic(&cell));
}

void CellFactory::deleteBehaviors(Cell& cell)
{
	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();
	if (cell.getThermicBehavior() != nullptr)
		delete cell.getThermicBehavior();
}
