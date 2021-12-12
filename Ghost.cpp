#include "Ghost.h"

//responsible for visual and logical ghost movement
void Ghost::step(const Position& pacmanLocation)
{
	Position::compass newDir = _direction;
	
	if (NoviceStrategy* s = dynamic_cast<NoviceStrategy*>(_strategy))
	{
		newDir = s->go(_location, _direction);
	}
	else if (GoodStrategy* s = dynamic_cast<GoodStrategy*>(_strategy))
	{
		newDir = s->go(_location, pacmanLocation, _direction);
	}
	else if (SmartStrategy* s = dynamic_cast<SmartStrategy*>(_strategy))
	{
		newDir = s->go(_location, pacmanLocation);
	}
	if (newDir != Position::compass::STAY)
	{
		setDirection(newDir);
	}
	move();
	_map->printTile(_location);
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
		_strategy = new NoviceStrategy;
		break;
	}
	case 2:
	{
		_strategy = new GoodStrategy;
		break;
	}
	case 3:
	{
		_strategy = new SmartStrategy;
		break;
	}
	}
}
