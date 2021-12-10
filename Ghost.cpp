#include "Ghost.h"

//responsible for visual and logical ghost movement
void Ghost::step()
{
	Position Ghostloc = _location;
	Position NextGhostloc = _location;

	NextGhostloc.update(_direction);

	if (isNextLocationWallorTunnel(NextGhostloc))
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
/*
Strategy* strategy;

setStrategy(int choice)
{
if(1)
strategy = new NoviceStrategy();
if(2)
strategy = new GoodStrategy();
if(3)
strategy = new BestStrategy();
----------------------------------> meaning we need a destructor, copy c'tor for Ghost!
Ghost::step()
{
strategy->go();
move();
_map->printTile(_location);
}

class Strategy
{
virtual void go = 0;
}

class BestStrategy
{
virtual void go()
{
smartGhostMove(); without move because we dot have ghost 
}
}

}

*/

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
