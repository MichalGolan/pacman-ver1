#ifndef _FRUIT_H
	#define _FRUIT_H

#include "Creature.h"

class Fruit : public Creature{
public:
	Fruit(Position::compass direction = Position::RIGHT, char figure = '5');

	void		 randFigure();
	void		 step();  // slow movment, random direction, 
	void		 stepSave(ofstream& steps, stringstream& ss);
	virtual void reset(); // choose random figure and location on map
	void		 activate();

	void setMap(Map* pMap);
	int	 getisActive() const; 

private:
	int _showTimer, _hideTimer, _active;
	NoviceStrategy _strategy;
};


#endif