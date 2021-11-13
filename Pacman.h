#ifndef _PACMAN_H
	#define _PACMAN_H

#include "Position.h"

class Pacman {

	Position _location;
	int _direction;
	char _figure;
	char _arrowKeys[5];
	Colour _colour;

public:
	Pacman(Position pos = { 1,1 }, int dir = 4, char figure = '@', Colour colour = WHITE);
	void setArrowKeys(const char* keys);  // "waxd s"
	void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(int dir);
	void setLocation(Position newLocation);

	Position getLocation();
	int getDirection();

	void move();
	int getDirectionKey(char key) const;
};


#endif