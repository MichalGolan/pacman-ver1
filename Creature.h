#ifndef _CREATURE_H
	#define _CREATURE_H

#include "General.h"
#include "Position.h"
#include "Map.h"

class Creature {
public:
	//c'tor
	Creature(Position location, Position::compass direction, char figure, Colour colour);

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

	void move();

	int      validMove(char& key);
	int      isNextLocationWallorTunnel(Position::compass dir, Position nextLocation) const;
	void     handleTunnel(Position pos);
	Position isATunnel(Position pos) const;
	int      notAPath() const;
	void     handlePacmanMove();
	void     handleGhostMove();



protected:
	Position              _location;
	Position::compass     _direction;
	char                  _figure;
	Colour                _colour;
	Map*				  _map;

};


#endif