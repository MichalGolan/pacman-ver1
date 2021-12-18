#include "Strategy.h"

Position::compass Strategy::goSmart(const Position& currGPos, const Position& PacmanPos)
{
	return _map->getBestRoute(PacmanPos, currGPos);
}


Position::compass Strategy::goDumb(const Position& currPos, const Position::compass& dir)
{
	Position Nextloc = currPos;
	Nextloc.update(dir);

	if (_map->isNextLocationWallorTunnel(Nextloc))
	{
		return _map->randDirection(currPos);
	}
	else
	{
		return dir;
	}
}
