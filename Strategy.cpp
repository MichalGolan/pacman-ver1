#include "Strategy.h"

Position::compass Strategy::goSmart(const Position& currGPos, const Position& PacmanPos)
{
	return _map->getBestRoute(PacmanPos, currGPos);
}


Position::compass Strategy::goDumb(const Position& currPos, const Position::compass& dir)
{
	Position NextGhostloc = currPos;
	NextGhostloc.update(dir);

	if (_map->isNextLocationWallorTunnel(NextGhostloc))
	{
		return _map->randDirection(currPos);
	}
	else
	{
		return dir;
	}
}
