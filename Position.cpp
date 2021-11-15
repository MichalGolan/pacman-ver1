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

void Position::update()  
{
	int dir = rand() % 4; //--> 0, 1, 2, 3
	update((compass)dir);
}

void Position::update(compass direction)
{
	switch (direction) {
	case UP: 
		--y;
		break;
	case DOWN: 
		++y;
		break;
	case LEFT:
		--x;
		break;
	case RIGHT:
		++x;
		break;
	case STAY:
		break;
	}
}

void Position::move(Colour colour, char c, compass direction)
{
	draw(' ');
	update(direction);
	setTextColour(colour);
	draw(c);
}

void Position::moveRand(Colour colour, char c)
{
	draw(' ');
	update();
	setTextColour(colour);
	draw(c);
}

int Position::operator==(const Position& other)
{
	return(x == other.x && y == other.y);
}

int Position::operator!=(const Position& other)
{
	return(x != other.x || y != other.y);
}
