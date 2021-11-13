#include "Ghost.h"

Position  Ghost::getLocation()
{
	return _location;
}

void Ghost::setColour(Colour c) {
	_colour = c;
}

void Ghost::setFigure(const char c) {
	_figure = c;
}

void Ghost::setDirection(int dir) {
	_direction = dir;
}

void Ghost::setLocation(Position loc)
{
	_location = loc;
}

void Ghost::move()
{
	//assuming the next move is valid --> this will be checked before the call for move
	// print ' '
	//update x y locatoin
	//colour
	//draw
	_location.draw(' ');
	_location.move(_direction);
	setTextColour(_colour);
	_location.draw(_figure);
}

