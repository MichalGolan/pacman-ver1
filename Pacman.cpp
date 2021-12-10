#include "Pacman.h"

// this function checks what is the next move according to: if a wall, a breadcrumb, a tunnel or a ghost. 
// it considers directions
void Pacman::step()
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

//reset to initial location
void Pacman::reset()
{
	_map->printTile(_location);
	setLocation(_map->getCorner(0));
	setDirection(Position::STAY);
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


int Pacman::getBCscore() const
{
	return _breadcrumbs;
}

int Pacman::getBonusPoints() const
{
	return _bonusPoints;
}

void Pacman::setBonusPoint(int x)
{
	_bonusPoints += x;
}

int Pacman::handleFruitMeet(const Position& fruitPos, char fruitFigure)
{
	int meet = 0;
	if(_location == fruitPos)
	{
		setBonusPoint(int(fruitFigure - '0'));
		meet = 1;
	}
	return meet;
}
