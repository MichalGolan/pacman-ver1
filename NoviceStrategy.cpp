#include "NoviceStrategy.h"

Position::compass NoviceStrategy::go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir)
{
	return goDumb(currGPos, dir);
}
