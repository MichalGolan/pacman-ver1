#ifndef _CREATURE_H
	#define _CREATURE_H

#include "General.h"
#include "Position.h"
#include "Map.h"

class Creature {
public:
	//c'tor
	Creature(char figure, Position::compass direction);

	//setters
	void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(int dir);
	void setDirection(Position::compass dir);
	void setLocation(Position newLocation);
	void setMap(Map* map);

	//getters
	Position               getLocation() const;
	Position::compass      getDirection() const;
	char				   getFigure() const;

	void			  move();
	Position::compass randDirection();
	virtual void	  step() = 0; 
	virtual void	  reset() = 0;

	int      isNextLocationWallorTunnel(const Position& nextLocation) const;

protected:
	Position              _location;
	Position::compass     _direction;
	char                  _figure;
	Colour                _colour;
	Map*				  _map;

};


#endif