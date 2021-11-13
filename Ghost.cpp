#include "Ghost.h"

Ghost::Ghost()
{
	_direction = 1;
	_figure = '$';
}

Ghost::Ghost(Position pos, int dir, Colour c = WHITE, const char figure = '$')
{
	_direction = dir;
	_colour = c;
	_figure = figure;
	_location = pos;
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

