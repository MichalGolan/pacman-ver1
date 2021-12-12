#include "Fruit.h"

Fruit::Fruit(Position::compass direction, char figure) : Creature(figure, direction), _showTimer(0)
{
	reset();
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
		_direction = _strategy.go(_location, _direction);
		move();
		_showTimer--;
	}
}

// get fruit to its initial state: NOT ACTIVE
void Fruit::reset()
{
	_hideTimer = randinRange(20, 10);
	_active = 0;
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
		}
	}
}