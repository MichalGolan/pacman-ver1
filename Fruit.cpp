#include "Fruit.h"

Fruit::Fruit(Position::compass direction, char figure) : Creature(figure, direction), _showTimer(0), _active(0)
{
	_hideTimer = randinRange(20, 10);
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
		reset(); //--> in here: _showTimer = randinRange(30, 20); + _active =  1; --> 
				 // if cant find goos random location will not switch to active!
	}
	else if (_showTimer == 0 && _active)
	{
		_hideTimer = randinRange(20, 10);
		_active = 0;
	}
	else if(!_active)
	{
		_hideTimer--;
	}
	else if (_active)
	{
		Position nextloc = _location;
		nextloc.update(_direction);

		if (isNextLocationWallorTunnel(_direction, nextloc)) // nextloc is wall or tunnel
		{
			//dumb ghost movement --> novice strategy (meaning: fruit will have data member noviceStrategy)
			//---------------------------------> come back and check this if after doing the novice strategy func
			//probably will return a good direction and then we use it somehow
			//strategy.go();
		}
		// nextloc good to go!
		move();
		_showTimer--;
	}
}

void Fruit::reset()
{

}