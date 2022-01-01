#include "Menu.h"

void start(int mode)
{
	int runGame = GO;
	switch (mode)
	{
	case 1: //reg
	{
		do
		{
			Game game;
			game.set(runGame);

		} while (runGame);
		break;
	}
	case 2: // save
	{
		Game* game = new SaveMode;
		game->set(runGame);
		break;
	}
	case 3: // load
	{
		//	_strategy = new SmartStrategy(_map);
		break;
	}
	case 4: // silent
	{

		//_strategy = new SmartStrategy(_map);
		break;
	}
	}

}