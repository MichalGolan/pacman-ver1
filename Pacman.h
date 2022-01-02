#ifndef _PACMAN_H
	#define _PACMAN_H

#include "Creature.h"

class Pacman : public Creature{

public:
	//c'tor
	Pacman(Position::compass direction = Position::STAY, char figure = '@') : Creature(figure, direction), _breadcrumbs(0), _bonusPoints(0) {}
	void step();
	void loadStep(Position::compass dir);
	virtual void reset();
	void handleTunnel(const Position& pos);

	int  getBCscore() const;
	void resetScore() { _breadcrumbs = 0; _bonusPoints = 0; }
	int  getBonusPoints() const;

	void setBonusPoint(int x);
	int handleFruitMeet(const Position& fruitPos, char fruitFigure, int isActive);

private:
	int    _breadcrumbs, _bonusPoints;
};


#endif