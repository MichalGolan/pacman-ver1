#include "Ghost.h"

Ghost::Ghost() : _location({ 1,1 }), _direction(Position::LEFT), _figure('$'), _colour(WHITE) {}

Ghost::Ghost(Position location, Position::compass direction, char figure, Colour colour)
{
	setLocation(location);
	setDirection(direction);
	setFigure(figure);
	setColour(colour);
}

Position  Ghost::getLocation() const
{
	return _location;
}

void Ghost::setColour(Colour c) {
	_colour = c;
}

void Ghost::setFigure(const char c) {
	_figure = c;
}

void Ghost::setDirection(Position::compass dir) {
	_direction = dir;
}

void Ghost::setLocation(Position loc)
{
	_location = loc;
}

void Ghost::move()
{
	_location.move(_colour, _figure, _direction);
}

