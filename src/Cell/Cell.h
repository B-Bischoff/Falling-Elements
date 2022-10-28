#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

class IMovementBehavior;
class IThermicBehavior;
class CellFactory;

enum CellType { Gazeous, Liquid, Solid};

class Cell {
protected:
	glm::vec3 _color;
	glm::vec2 _position;
	CellType _type;

	Cell** _cells;
	int _width, _height;

	IMovementBehavior* _movementBehavior;
	IThermicBehavior* _thermicBehavior;

	glm::vec2 _velocity;

public:
	Cell();
	~Cell();

	double _thermalConductivity;
	double _temperature;
	double _nextTemperature;
	double _density;
    double _friction;

	bool update();
	void swapCell(Cell& rhs);

	void setCells(Cell** cells);
	Cell** getCells(void) const;
	void setWidth(const int& width);
	const int& getWidth(void) const;
	void setHeight(const int& height);
	const int& getHeight(void) const;
	void setColor(const glm::vec3& color);
	const glm::vec3& getColor() const;
	void setPosition(const glm::vec2& position);
	const glm::vec2& getPosition() const;
	void setMovementBehavior(IMovementBehavior* behavior);
	IMovementBehavior* getMovementBehavior(void) const;
	void SetThermicBehavior(IThermicBehavior* behavior);
	IThermicBehavior* getThermicBehavior(void) const;
	void setType(const CellType& type);
	const CellType& getType(void) const;
	void setVelocity(const glm::vec2 velocity);
	const glm::vec2& getVelocity() const;

	Cell& operator=(const Cell& rhs);
};

std::ostream& operator<<(std::ostream& o, const Cell& cell);
