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

Position::compass Ghost::getDirection() const
{
	return _direction;
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

//changes ghost's direction so it goes back and forth
void Ghost::switchDirection()
{
	int currdir = _direction;
	if (currdir % 2 == 0)
	{
		currdir++;
	}
	else
	{
		currdir--;
	}
	_direction = (Position::compass)currdir;
}

//calls move for Position of ghost
void Ghost::move()
{
	_location.move(_colour, _figure, _direction);
}

