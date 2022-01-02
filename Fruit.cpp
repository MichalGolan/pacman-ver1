#include "Fruit.h"

Fruit::Fruit(Position::compass direction, char figure) : Creature(figure, direction), _showTimer(0)
{
	_hideTimer = randinRange(20, 10);
	_active = 0;
}

void Fruit::randFigure()
{
	char figure = '0' + randinRange(9, 5);   //rand -->  0, 1, 2, 3, 4 // rand + 5 --> 5, 6, 7, 8, 9, 
	setFigure(figure);
}

void Fruit::step()
{
	if (_hideTimer == 0 && !_active) // still in hide mode
	{
		activate(); // if cant find good random location will not switch to active!
	}
	else if (_showTimer == 0 && _active)
	{
		reset();
	}
	if(!_active)
	{
		_hideTimer--;
	}
	else if (_active)
	{
		Position prevPos = _location;

		_direction = _strategy.go(_location, _location, _direction);
		move();
		_showTimer--;
		_map->printTile(prevPos);
	}
}

void Fruit::stepSave(ofstream& steps)
{
	int firstAppear = 0;
	if (_hideTimer == 0 && !_active) // still in hide mode
	{
		activate(); // if cant find good random location will not switch to active!
		if (_active)
		{
			firstAppear = 1;
		}
	}
	else if (_showTimer == 0 && _active)
	{
		reset();
	}
	if (!_active)
	{
		steps << "f" << "n" << " ";
		_hideTimer--;
	}
	else if (_active)
	{
		Position prevPos = _location;
		if (firstAppear)
		{
			steps << "f" << "f" << _figure << _direction << _location << " ";
			firstAppear = 0;
		}
		else
		{
			steps << "f" << "a" << _direction  << " ";
		}
		_direction = _strategy.go(_location, _location, _direction);
		move();
		_showTimer--;
		_map->printTile(prevPos);
	}
}
// get fruit to its initial state: NOT ACTIVE
void Fruit::reset()
{
	_hideTimer = randinRange(20, 10);
	_active = 0;
	_map->printTile(_location);
}


//activate fruit 
void Fruit::activate()
{
	int found = 0;
	Position newPos;
	newPos.randPos(_map->getHeight(), _map->getWidth());
	for (int i = 0; i < 10 && !found; i++)
	{
		newPos.randPos(_map->getHeight(), _map->getWidth());
		if (!_map->isNextLocationWallorTunnel(newPos))
		{
			found = 1;
			_showTimer = randinRange(30, 20);
			_active = 1;
			randFigure();
			_location = newPos;
		}
	}
	if (_active == 0)
	{
		_hideTimer++;
	}
}

void Fruit::setMap(Map* pMap)
{
	Creature::setMap(pMap);
	_strategy.setMap(pMap);
}

int	 Fruit::getisActive() const
{
	return _active;
}