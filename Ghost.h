#ifndef _GHOST_H
	#define _GHOST_H

#include "Creature.h"

class Ghost : public Creature{

public:
	//c'tors
	Ghost(Position location, char figure = '$', Position::compass direction = Position::LEFT) : Creature(figure, direction) {_location = location;}

	virtual void     step();
	virtual void	 reset();
	void     smartGhostMove(const Position& pacmanPosition);
	void	 switchDirection();
};


#endif