#include "Position.h"

void Position::setXY(int _x, int _y)
{
	x = _x;
	y = _y;
}


void Position::draw(char ch) const
{
	gotoxy(x, y);
	cout << ch << endl;
}

void Position::move()  
{
	int dir = rand() % 4;
	move(dir);
}

void Position::move(int direction)
{
	switch (direction) {
	case 0: // UP
		--y;
		break;
	case 1: // DOWN
		++y;
		break;
	case 2: // LEFT
		--x;
		break;
	case 3: // RIGHT
		++x;
		break;
	case 4: // STAY
		break;
	}
}

int Position::compare(Position a)
{
	return (a.x == x && a.y == y);
}