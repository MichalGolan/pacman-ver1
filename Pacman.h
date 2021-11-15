#ifndef _PACMAN_H
	#define _PACMAN_H

#include "Position.h"

class Pacman {

public:
	Pacman(Position pos = { 2,1 }, Position::compass dir = Position::STAY, char figure = '@', Colour colour = WHITE);

	void setArrowKeys(const char* keys);  // "waxd s"
	void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(int dir);
	void setDirection(Position::compass dir);
	void setLocation(Position newLocation);

	Position               getLocation() const;
	Position::compass      getDirection() const;

	void move();
	int  getDirectionKey(char key) const;

private:
	Position _location;
	Position::compass _direction;
	char _figure;
	char _arrowKeys[5];
	Colour _colour;
};


#endif