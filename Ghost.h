#ifndef _GHOST_H
	#define _GHOST_H

#include "Position.h"
#include "Creature.h"

class Ghost : public Creature{

public:
	//c'tors
	Ghost();
	Ghost(Position location, Position::compass direction, char figure, Colour colour = WHITE);


	void switchDirection();
};


#endif