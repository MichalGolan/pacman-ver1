#ifndef _POSITION_H
	#define _POSITION_H
 
#include "General.h"

class Position {
	int x;
	int y;

public:
	Position(int _x = 1, int _y = 1) : x(_x), y(_y) {}; 
	void draw(char ch) const;
	void move() ;
	void move(int direction);
};

#endif