#include "Pacman.h"

Pacman::Pacman(Position pos, Position::compass dir, char figure, Colour colour)
{
	setLocation(pos);
	setDirection(dir);
	setFigure(figure);
	setColour(colour);
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
	_direction = (Position::compass)dir;
}

void Pacman::setDirection(Position::compass dir) {
	_direction = dir;
}

void Pacman::setLocation(Position newLocation)
{
	_location = newLocation;
}

Position Pacman::getLocation() const
{
	return _location;
}

Position::compass Pacman::getDirection() const
{
	return _direction;
}

//calls for move of Position
void Pacman::move()
{
	_location.move(_colour, _figure, _direction);
}

//returns the direction by given key according to our arrow keys
int Pacman::getDirectionKey(char key) const
{
	for (int i = 0; i < 5; i++)
	{
		if (key == _arrowKeys[i])
			return i;
	}
	return -1;
}

