#include "Ghost.h"

//responsible for visual and logical ghost movement
void Ghost::step()
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

//reset location to ghost initial location
void Ghost::reset()
{
	_map->printTile(_location);
	setLocation(_map->getCorner(1));
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
