#ifndef _STRATEGY_H
	#define _STRATEGY_H

#include "Position.h"
#include "Map.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>


class Strategy {

public:
	virtual ~Strategy() {}
	virtual Position::compass go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir) = 0;

protected:
	Strategy() {}

	virtual Position::compass goSmart(const Position& currGPos, const Position& PacmanPos);
	virtual Position::compass goDumb(const Position& currPos, const Position::compass& dir);
	virtual Position::compass randRoute(const Position& currPos);

	Map* _map = nullptr;
};

#endif
