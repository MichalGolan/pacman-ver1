#ifndef _POSITION_H
	#define _POSITION_H
 
#include "General.h"

class Position {
	int x;
	int y;
	friend class Game;	
	friend class Map;
	
public:
	Position(int _x = 1, int _y = 1) : x(_x), y(_y) {}; 
	void setXY(int _x, int _y);
	void draw(char ch) const;
	void move() ;
	void move(int direction);
	int compare(Position a);
};

#endif