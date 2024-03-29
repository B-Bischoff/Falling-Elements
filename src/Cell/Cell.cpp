#include "Cell.h"
#include "MovementBehavior/IMovementBehavior.h"
#include "ThermicBehavior/IThermicBehavior.h"
#include "Factory/CellFactory.h"

Cell::Cell()
	: _color(glm::vec3(0.2f, 0.0f, 0.2f)), _position(glm::vec2(0.0f)), _movementBehavior(nullptr), _thermicBehavior(nullptr), _type(CellType::Gazeous),
		_velocity(0.0f), _temperature(20), _nextTemperature(20), _thermalConductivity(1), _density(2), _friction(1)
{
}

Cell::~Cell()
{
}

bool Cell::update()
{
	if (!_movementBehavior->hasMoved)
	{
		_movementBehavior->hasMoved = true;
		_thermicBehavior->update();
		_movementBehavior->update();
		return true;
	}
	return false;
}

void Cell::swapCell(Cell& rhs)
{
	Cell temp(*this);
	*this = rhs;
	rhs = temp;
}

void Cell::setCells(Cell** cells) { _cells = cells; }

Cell** Cell::getCells(void) const { return _cells; }

void Cell::setWidth(const int& width) { _width = width; }

const int& Cell::getWidth(void) const { return _width; }

void Cell::setHeight(const int& height) { _height = height; }

const int& Cell::getHeight(void) const { return _height; }

void Cell::setColor(const glm::vec3& color) { _color = color; }

const glm::vec3& Cell::getColor() const { return _color; }

void Cell::setPosition(const glm::vec2& position) { _position = position; }

const glm::vec2& Cell::getPosition() const { return _position; }

void Cell::setMovementBehavior(IMovementBehavior* behavior) { _movementBehavior = behavior; }

IMovementBehavior* Cell::getMovementBehavior(void) const { return _movementBehavior; }

void Cell::SetThermicBehavior(IThermicBehavior* behavior) { _thermicBehavior = behavior; }

IThermicBehavior* Cell::getThermicBehavior(void) const { return _thermicBehavior; }

void Cell::setType(const CellType& type) { _type = type; }

const CellType& Cell::getType(void) const { return _type; }

void Cell::setVelocity(const glm::vec2 velocity) { _velocity = velocity; }

const glm::vec2& Cell::getVelocity() const { return _velocity; }

Cell& Cell::operator=(const Cell& rhs)
{
	if (&rhs == this)
		return *this;

	_color = rhs._color;
	_type = rhs._type;
	_movementBehavior = rhs._movementBehavior;
	_movementBehavior->setCell(this);
	_thermicBehavior = rhs._thermicBehavior;
	_thermicBehavior->setCell(this);
	_velocity = rhs._velocity;
	_temperature = rhs._temperature;
	_nextTemperature = rhs._nextTemperature;
	_density = rhs._density;
	_thermalConductivity = rhs._thermalConductivity;

	return *this;
}

std::ostream& operator<<(std::ostream& o, const Cell& cell)
{
	o << "Cell[" << cell.getPosition().y << "][" << cell.getPosition().x << "]" << std::endl;
	o << "Color: R(" << cell.getColor().r << ") G(" << cell.getColor().g << ") B(" << cell.getColor().b << ")" << std::endl;
	o << "Solid: " << cell.getType() << std::endl;

	return o;
}

