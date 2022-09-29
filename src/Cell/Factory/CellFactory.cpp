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

	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();
	
	cell.setMovementBehavior(new SandBehavior(&cell));
}

void CellFactory::configureWaterCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.6f, 1.0f));
	cell.setType(CellType::Liquid);
	cell._temperature = 10;

	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();
	
	cell.setMovementBehavior(new WaterBehavior(&cell));
}

void CellFactory::configureRockCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.2f, 0.2f));
	cell.setType(CellType::Solid);
	cell._temperature = 0;
	
	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();

	cell.setMovementBehavior(new StaticBehavior(&cell));
}

void CellFactory::configureAirCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.0f, 0.2f));
	cell.setType(CellType::Gazeous);
	cell._temperature = 20;
	cell._density = 2;
	
	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();

	cell.setMovementBehavior(new IMovementBehavior(&cell));
}

void CellFactory::configureSmokeCell(Cell& cell)
{
	float r = (80 - rand() % 6) / 100.0f;
	float g = (80 - rand() % 6) / 100.0f;
	float b = (80 - rand() % 6) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Gazeous);
	cell._temperature = 20;
	cell._density = 1;
	
	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();

	cell.setMovementBehavior(new SmokeBehavior(&cell));
}
