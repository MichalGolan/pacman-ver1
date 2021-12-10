#ifndef _POSITION_H
	#define _POSITION_H
 
#include "General.h"

class Position {
public:
	enum compass { UP, DOWN, LEFT, RIGHT, STAY };
	
public:
	Position(int _x = 1, int _y = 1) : x(_x), y(_y) {}; 

	void setXY(int _x, int _y);

	void draw(char ch) const;

	void update(compass direction);
	void move(Colour colour, char c, compass direction);
	void gotoPos();
	Position randPos(int bottom, int right);

	int  operator==(const Position& other);
	int  operator!=(const Position& other);

private:
	int x;
	int y;

	friend class Game;
	friend class Creature;
	friend class Map;
};

#endif