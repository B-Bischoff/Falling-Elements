#pragma once

#include <iostream>
#include "IMovementBehavior.h"
#include "ParticleBehavior.h"

class IMovementBehavior;

class SandBehavior : public IMovementBehavior {
private:
	int _x, _y;
	int _random;
	Cell* _target;

public:
	SandBehavior(Cell* cell) : IMovementBehavior(cell) { };
	~SandBehavior() {};

	void update()
	{
		_target = nullptr;
		_x = _cell->getPosition().x;
		_y = _cell->getPosition().y;

		if (_y < _cell->getHeight() - 1)
		{
			_random = (rand() % 2) * 2 - 1; // 'random' can be -1 or 1

			checkBelowCells();
			
			if (cellHasVelocity() == true)
			{
				if (targetFound() == false)
					CheckAdjacentBelowCells();
				if (targetFound() == false)
					transmitVelocity();
			}

			if (targetFound() == true)
			{
				updateVelocity();
				_cell->swapCell(*_target);
			}
		}

		if (targetFound() == false && cellHasVelocity() == true)
			_cell->setMovementBehavior(new ParticleBehavior(_cell, *this));
	}

private:
	void checkBelowCells()
	{
		for (int i = 0; i <= _cell->getVelocity().y; i++)
		{
			if ((_y + i + 1) < _cell->getHeight() && _cells[_y + i + 1][_x].getType() < CellType::Solid)
				_target = &(_cells[_y + i + 1][_x]);
			else
				break;
		}
	};

	void CheckAdjacentBelowCells()
	{
		if (_x - _random >= 0 && _x - _random < _cell->getWidth() && _cells[_y + 1][_x - _random].getType() < CellType::Solid)
			_target = &(_cells[_y + 1][_x - _random]);
		else if (_x + _random >= 0 && _x + _random < _cell->getWidth() && _cells[_y + 1][_x + _random].getType() < CellType::Solid)
			_target = &(_cells[_y + 1][_x + _random]);
	};

	void updateVelocity()
	{
		if (_target->getType() == CellType::Gazeous) // Accelerate in free falling
			_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, 0.20f));
		else if (_target->getType() == CellType::Liquid && _cell->getVelocity().y > 0.8f) // Get slow done by liquid
			_cell->setVelocity(_cell->getVelocity() + glm::vec2(0.0f, -0.8f));
	};

	void transmitVelocity()
	{
		const float X_FRI = 0.50f;
		const float Y_FRI = 0.25f;

		// Transmit half the velocity to the cell below
		if (_y < _cell->getHeight() - 1 && _cells[_y + 1][_x].getType() == CellType::Solid && _cells[_y+1][_x].getVelocity()==glm::vec2(0.0f))
		{
			glm::vec2 velocity = _cell->getVelocity();
			glm::vec2 targetVelocity = _cells[_y + 1][_x].getVelocity();
			glm::vec2 finalVelocity = targetVelocity + (velocity * Y_FRI);
			_cells[_y + 1][_x].setVelocity(finalVelocity);
		}

		// Transmit half the velocity to the cell below left
		if (_y < _cell->getHeight() - 1 && _x > 0 && _cells[_y + 1][_x - 1].getType() == CellType::Solid && _cells[_y+1][_x-1].getVelocity()==glm::vec2(0.0f))
		{
			glm::vec2 velocity = _cell->getVelocity();
			glm::vec2 targetVelocity = _cells[_y + 1][_x - 1].getVelocity();
			glm::vec2 finalVelocity = targetVelocity + glm::vec2(-velocity.y * X_FRI, velocity.y * Y_FRI);
			_cells[_y + 1][_x - 1].setVelocity(finalVelocity);
		}

		// Transmit half the velocity to the cell below right
		if (_y < _cell->getHeight() - 1 && _x < _cell->getWidth() - 1 && _cells[_y + 1][_x + 1].getType() == CellType::Solid && _cells[_y+1][_x+1].getVelocity()==glm::vec2(0.0f))
		{
			glm::vec2 velocity = _cell->getVelocity();
			glm::vec2 targetVelocity = _cells[_y + 1][_x + 1].getVelocity();
			glm::vec2 finalVelocity = targetVelocity + glm::vec2(velocity.y * X_FRI, velocity.y * Y_FRI);
			_cells[_y + 1][_x + 1].setVelocity(finalVelocity);
		}

		// Transmit half the velocity to the cell left
		if (_x > 0 && _cells[_y][_x - 1].getType() == CellType::Solid && _cells[_y][_x-1].getVelocity()==glm::vec2(0.0f))
		{
			glm::vec2 velocity = _cell->getVelocity();
			glm::vec2 targetVelocity = _cells[_y][_x - 1].getVelocity();
			glm::vec2 finalVelocity = targetVelocity + glm::vec2(velocity.y * X_FRI, velocity.y * Y_FRI);
			_cells[_y][_x - 1].setVelocity(finalVelocity);
		}

		// Transmit half the velocity to the cell right
		if (_x < _cell->getWidth() - 1 && _cells[_y][_x + 1].getType() == CellType::Solid && _cells[_y][_x+1].getVelocity()==glm::vec2(0.0f))
		{
			glm::vec2 velocity = _cell->getVelocity();
			glm::vec2 targetVelocity = _cells[_y][_x + 1].getVelocity();
			glm::vec2 finalVelocity = targetVelocity + glm::vec2(velocity.y * X_FRI, velocity.y * Y_FRI);
			_cells[_y][_x + 1].setVelocity(finalVelocity);
		}

		float yVel = _cell->getVelocity().y;
		_cell->setVelocity(glm::vec2(yVel * 0.50f * _random, yVel * 0.25f));
	}

	const bool targetFound()
	{
		return _target;
	}

	const bool cellHasVelocity()
	{
		return _cell->getVelocity() != glm::vec2(0.0f);
	}
};
