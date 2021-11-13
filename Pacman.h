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
	void setArrowKeys(const char* keys) { // "waxd s"
		_arrowKeys[0] = keys[0];
		_arrowKeys[1] = keys[1];
		_arrowKeys[2] = keys[2];
		_arrowKeys[3] = keys[3];
		_arrowKeys[4] = keys[4];
	}
	void setColour(Colour c) {
		_colour = c;
	}
	void setFigure(const char c) {
		_figure = c;
	}
	void move();
	int getDirectionKey(char key);
	void setDirection(int dir) {
		_direction = dir;
	}
};


#endif