#include "Ghost.h"

Ghost::Ghost() : Creature({ 1,1 }, Position::LEFT, '$', WHITE) {}

Ghost::Ghost(Position location, Position::compass direction, char figure, Colour colour) : Creature(location, direction, figure, colour)
{
/*	setLocation(location);
	setDirection(direction);
	setFigure(figure);
	setColour(colour);*/ //mimi
}

/*Position  Ghost::getLocation() const
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
}*/ // mimi

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
/*void Ghost::move()
{
	_location.move(_colour, _figure, _direction);
}*/ //mimi

