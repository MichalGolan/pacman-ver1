#ifndef _SMARTSTRATEGY_H
	#define _SMARTSTRATEGY_H

#include "Strategy.h"

class SmartStrategy : public Strategy
{
public:
	Position::compass go(const Position& currGPos, const Position& PacmanPos);


};
#endif