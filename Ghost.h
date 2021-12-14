#ifndef _GHOST_H
	#define _GHOST_H

#include "Creature.h"
#include "GoodStrategy.h"
#include "SmartStrategy.h"

class Ghost : public Creature{

public:
	//c'tors
	Ghost(const Position& location, char figure = '$', Position::compass direction = Position::LEFT) : _startingPos(location), Creature(figure, direction) {_location = location;}
	virtual ~Ghost();

	void			 step(const Position& pacmanLocation);
	virtual void	 reset();

	void setStrategy(int index);

private:
	Strategy* _strategy = nullptr;
	const Position  _startingPos;
};


#endif