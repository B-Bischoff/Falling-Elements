#include "CellFactory.h"

void CellFactory::configureSandCell(Cell& cell)
{
	float r = (100 - rand() % 6) / 100.0f;
	float g = (85 - rand() % 11) / 100.0f;
	float b = (65 - rand() % 11) / 100.0f;

	cell.setColor(glm::vec3(r, g, b));
	cell.setType(CellType::Solid);

	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();
	
	cell.setMovementBehavior(new SandBehavior(&cell));
}

void CellFactory::configureWaterCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.6f, 1.0f));
	cell.setType(CellType::Liquid);

	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();
	
	cell.setMovementBehavior(new WaterBehavior(&cell));
}

void CellFactory::configureRockCell(Cell& cell)
{
	cell.setColor(glm::vec3(0.2f, 0.2f, 0.2f));
	cell.setType(CellType::Solid);
	
	if (cell.getMovementBehavior() != nullptr)
		delete cell.getMovementBehavior();

	cell.setMovementBehavior(new StaticBehavior(&cell));
}