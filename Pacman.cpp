#include "Pacman.h"

Pacman::Pacman(Position pos = {1,2}, int dir = 4, char figure = '@', Colour colour = WHITE)
{
	_location = pos;
	_direction = dir;
	_figure = figure;
	_colour = colour; 
	setArrowKeys("wxads");
}


void Pacman::setArrowKeys(const char* keys) { // "waxd s"
	_arrowKeys[0] = keys[0];
	_arrowKeys[1] = keys[1];
	_arrowKeys[2] = keys[2];
	_arrowKeys[3] = keys[3];
	_arrowKeys[4] = keys[4];
}

void Pacman::setColour(Colour c) {
	_colour = c;
}

void Pacman::setFigure(const char c) {
	_figure = c;
}

void Pacman::setDirection(int dir) {
	_direction = dir;
}

void Pacman::setLocation(Position newLocation)
{
	_location = newLocation;
}

Position Pacman::getLocation()
{
	return _location;
}

int Pacman::getDirection()
{
	return _direction;
}


void Pacman::move()
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

int Pacman::getDirectionKey(char key) const
{
	for (int i = 0; i < 5; i++)
	{
		if (key == _arrowKeys[i])
			return i;
	}
	return -1;
}

