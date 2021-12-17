#include "Ghost.h"

Ghost::~Ghost()
{
	delete _strategy;
}


//responsible for visual and logical ghost movement
void Ghost::step(const Position& pacmanLocation)
{
	Position prevPos = _location;
	 _direction = _strategy->go(_location, pacmanLocation, _direction);
	move();
	_map->printTile(prevPos);
}

//reset location to ghost initial location
void Ghost::reset()
{
	_map->printTile(_location);
	setLocation(_startingPos);
}

//set strategy by index from user
void Ghost::setStrategy(int index)
{
	switch (index)
	{
	case 1:
	{
		_strategy = new NoviceStrategy(_map);
		break;
	}
	case 2:
	{
		_strategy = new GoodStrategy(_map);
		break;
	}
	case 3:
	{
		_strategy = new SmartStrategy(_map);
		break;
	}
	}
}
