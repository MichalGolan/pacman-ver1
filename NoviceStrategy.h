#ifndef _NOVICETRATEGY_H
	#define _NOVICESTRATEGY_H

#include "Strategy.h"

class NoviceStrategy : public Strategy
{
public:
	Position::compass go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir);


};

#endif