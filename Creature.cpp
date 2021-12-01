#include "Creature.h"

Creature::Creature(Position location, Position::compass direction, char figure, Colour colour) 
{
	setLocation(location);
	setDirection(direction);
	setFigure(figure);
	setColour(colour);
}

void Creature::setColour(Colour c) {
	_colour = c;
}

void Creature::setFigure(const char c) {
	_figure = c;
}

void Creature::setDirection(int dir) {
	_direction = (Position::compass)dir;
}

void Creature::setDirection(Position::compass dir) {
	_direction = dir;
}

void Creature::setLocation(Position newLocation) {
	_location = newLocation;
}

void Creature::setMap(Map* map)
{
	//_map = *(map);
}
//calls for move of Position
void Creature::move()
{
	_location.move(_colour, _figure, _direction);
}

Position Creature::getLocation() const
{
	return _location;
}

Position::compass Creature::getDirection() const
{
	return _direction;
}