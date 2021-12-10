#include "Position.h"

//set x and y 
void Position::setXY(int _x, int _y)
{
	x = _x;
	y = _y;
}

//goes to (x,y) coordinate and pronts a given char there
void Position::draw(char ch) const
{
	gotoxy(x, y);
	cout << ch << endl;
}

//receives direction and moves (x,y) coordinate by it
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

//function for visual movement by a given direction 
void Position::move(Colour colour, char c, compass direction)
{
	draw(' ');
	update(direction);
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

void Position::gotoPos()
{
	gotoxy(x, y);
}

Position Position::randPos(int bottom, int right)
{
	Position rand;
	rand.x = randinRange(right);
	rand.y = randinRange(bottom);
	return rand;
}