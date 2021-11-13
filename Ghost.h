#ifndef _GHOST_H
	#define _GHOST_H

#include "Position.h"


class Ghost {

	Position _location;
	int _direction;
	char _figure;
	Colour _colour;

public:
	Position getLocation();
	void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(int dir);
	void setLocation(Position loc);
	void move();
	
};


#endif