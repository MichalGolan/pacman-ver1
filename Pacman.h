#ifndef _PACMAN_H
	#define _PACMAN_H

#include "Position.h"
#include "Creature.h"

class Pacman : public Creature{

public:
	//c'tor
	Pacman(Position location = { 2,1 },  Position::compass direction = Position::STAY, char figure = '@', Colour colour = WHITE);

	// void move(); mimi

	//setters
	/*void setColour(Colour c);
	void setFigure(const char c);
	void setDirection(int dir);
	void setDirection(Position::compass dir);
	void setLocation(Position newLocation);*/ //mimi

	//getters
	/*Position               getLocation() const;
	Position::compass      getDirection() const;*/
	//int                  getDirectionKey(char key) const;


/*private:
	void setArrowKeys(const char* keys);  // "waxd s"
	*/ //mimi 
private:
	/*Position _location;
	Position::compass _direction;
	char _figure;
	//char _arrowKeys[5]; mimi
	Colour _colour;*/
};


#endif