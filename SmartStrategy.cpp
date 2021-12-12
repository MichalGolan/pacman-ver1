#include "SmartStrategy.h"

Position::compass SmartStrategy::go(const Position& currGPos, const Position& PacmanPos)
{
	return goSmart(currGPos, PacmanPos);
}