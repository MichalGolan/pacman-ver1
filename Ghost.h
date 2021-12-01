#ifndef _GHOST_H
	#define _GHOST_H

#include "Position.h"
#include "Creature.h"

class Ghost : public Creature{

public:
	//c'tors
	Ghost();
	Ghost(Position location, Position::compass direction, char figure, Colour colour = WHITE);

	//getters
	/*Position               getLocation() const;
	Position::compass      getDirection() const;*/ // mimi

	//setters
	/*void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(Position::compass dir);
	void setLocation(Position loc);*/ //mimi
	void switchDirection();
	//void move(); mimi

private: //data members
	/*Position              _location;
	Position::compass     _direction;
	char                  _figure;
	Colour                _colour;*/
};


#endif