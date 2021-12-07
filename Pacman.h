#ifndef _PACMAN_H
	#define _PACMAN_H

#include "Position.h"
#include "Creature.h"

class Pacman : public Creature{

public:
	//c'tor
	Pacman(Position::compass direction = Position::STAY, char figure = '@') : Creature(figure, direction), _breadcrumbs(0) {}
	void handlePacmanMove();
	void handleTunnel(const Position& pos);


private:
	int    _breadcrumbs;
};


#endif