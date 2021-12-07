#include "Ghost.h"

//responsible for visual and logical ghost movement
void Ghost::handleGhostMove()
{
	Position Ghostloc = _location;
	Position NextGhostloc = _location;

	NextGhostloc.update(_direction);

	if (isNextLocationWallorTunnel(_direction, NextGhostloc))
	{
		switchDirection();
	}
	move();
	_map->printTile(Ghostloc);
}

void Ghost::smartGhostMove(const Position& pacmanPosition)
{
	Position::compass newDir = _map->getBestRoute(pacmanPosition, _location);
	setDirection(newDir);
	
	move();
	_map->printTile(_location);
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
