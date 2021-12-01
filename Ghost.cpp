#include "Ghost.h"

Ghost::Ghost() : Creature({ 1,1 }, Position::LEFT, '$', WHITE) {}

Ghost::Ghost(Position location, Position::compass direction, char figure, Colour colour) : Creature(location, direction, figure, colour)
{}


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
