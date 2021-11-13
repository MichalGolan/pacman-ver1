#include "Pacman.h"

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

int Pacman::getDirectionKey(char key)
{
	for (int i = 0; i < 5; i++)
	{
		if (key == _arrowKeys[i])
			return i;
	}
	return -1;
}