#ifndef _GHOST_H
	#define _GHOST_H

#include "Position.h"
#include "Creature.h"

class Ghost : public Creature{

public:
	//c'tors
	Ghost(Position location, char figure = '$', Position::compass direction = Position::LEFT) : Creature(figure, direction) {_location = location;}

	void     handleGhostMove();
	void     smartGhostMove(const Position& pacmanPosition);
	void	 switchDirection();
};


#endif