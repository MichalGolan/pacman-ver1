#ifndef _CREATURE_H
	#define _CREATURE_H

#include "General.h"
#include "Position.h"
#include "Map.h"
#include "NoviceStrategy.h"


class Creature {
public:
	//c'tor
	virtual ~Creature() {}
	Creature(char figure, Position::compass direction);

	//setters
	void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(int dir);
	void setDirection(Position::compass dir);
	void setLocation(const Position& newLocation);
	void setMap(Map* map);

	//getters
	Position               getLocation() const;
	Position::compass      getDirection() const;
	char				   getFigure() const;

	void			  move();
	Position::compass randDirection();

	virtual void	  reset() = 0;

protected:
	Position              _location;
	Position::compass     _direction;
	char                  _figure;
	Colour                _colour;
	Map*				  _map;

};


#endif