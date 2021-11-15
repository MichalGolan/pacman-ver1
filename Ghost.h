#ifndef _GHOST_H
	#define _GHOST_H

#include "Position.h"


class Ghost {

public:
	//c'tors
	Ghost();
	Ghost(Position location, Position::compass direction, char figure, Colour colour);

	//getters
	Position getLocation() const;

	//setters
	void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(Position::compass dir);
	void setLocation(Position loc);
	void move();

private: //data members
	Position              _location;
	Position::compass     _direction;
	char                  _figure;
	Colour                _colour;
	
};


#endif