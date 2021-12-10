#ifndef _FRUIT_H
	#define _FRUIT_H

#include "Creature.h"

class Fruit : public Creature{
public:
	Fruit(Position::compass direction = Position::STAY, char figure = '5');

	void randFigure();
	virtual void step();  // slow movment, random direction, 
	virtual void reset(); // choose random figure and location on map

	//handle fruit-pacman meet
	//handle fruit-ghost meet

private:
	int _appearTime;
};


#endif