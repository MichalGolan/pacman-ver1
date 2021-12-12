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
		return randRoute(currPos);
	}
	else
	{
		return (Position::compass::STAY);
	}
}

Position::compass Strategy::randRoute(const Position& currPos)
{
	array<Position::compass, 4> dirs{ Position::compass::UP, Position::compass::DOWN, Position::compass::LEFT, Position::compass::RIGHT };
	unsigned scrambler = chrono::system_clock::now().time_since_epoch().count();

	shuffle(dirs.begin(), dirs.end(), default_random_engine(scrambler));

	Position NextGhostloc;
	int i = 0, found = 0;
	while (i < 4 && !found)
	{
		NextGhostloc = currPos;
		NextGhostloc.update(dirs[i]);
		if (_map->isNextLocationWallorTunnel(NextGhostloc))
		{
			i++;
		}
		else
		{
			found = 1;
		}
	}
	if (!found)
	{
		return Position::compass::STAY;
	}
	else
	{
		return dirs[i];
	}
}
