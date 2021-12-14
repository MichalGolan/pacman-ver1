#include "SmartStrategy.h"

Position::compass SmartStrategy::go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir)
{
	return goSmart(currGPos, PacmanPos);
}