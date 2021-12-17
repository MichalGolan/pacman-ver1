#ifndef _STRATEGY_H
	#define _STRATEGY_H

#include "Map.h"

class Strategy {

public:
	virtual ~Strategy() {}
	virtual Position::compass go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir) = 0;
	void setMap(Map* pMap) { _map = pMap; }

protected:
	Strategy(Map* pMap) : _map(pMap) {}
	Position::compass goSmart(const Position& currGPos, const Position& PacmanPos);
	Position::compass goDumb(const Position& currPos, const Position::compass& dir);


	Map* _map;
};

#endif
