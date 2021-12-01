#ifndef _PACMAN_H
	#define _PACMAN_H

#include "Position.h"
#include "Creature.h"

class Pacman : public Creature{

public:
	//c'tor
	Pacman(Position location = { 2,1 },  Position::compass direction = Position::STAY, char figure = '@', Colour colour = WHITE);

};


#endif