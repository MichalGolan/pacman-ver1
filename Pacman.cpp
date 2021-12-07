#include "Pacman.h"

// this function checks what is the next move according to: if a wall, a breadcrumb, a tunnel or a ghost. 
// it considers directions
void Pacman::handlePacmanMove()
{
	Position nextpos = _location;
	int wallorTunnel = isNextLocationWallorTunnel(_direction, nextpos);

	if (wallorTunnel == 2)  // tunnel
	{
		handleTunnel(nextpos);
	}
	else if (wallorTunnel == 1) //wall 
	{
		_direction = Position::STAY;
	}
	else if (_map->getTileType(nextpos) == Map::BREADCRUMB) // not a wall --> check if BC
	{
		_map->setTile(nextpos, Map::EMPTY);
		_breadcrumbs++;
	}
}

//handling the movement for a tunnel
void Pacman::handleTunnel(const Position& pos)
{
	Position newPos = isATunnel(pos);
	if (newPos == pos)
	{
		setDirection(Position::STAY); 
	}
	else
	{
		_map->printTile(getLocation());
		setLocation(newPos);
	}
}