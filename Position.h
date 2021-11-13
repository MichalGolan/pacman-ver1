#ifndef _POSITION_H
	#define _POSITION_H
 
#include "General.h"

class Position {
	int x = 1, y = 1;
public:
	void draw(char ch);
	void move();
	void move(int direction);
};

#endif