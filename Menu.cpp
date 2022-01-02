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
		delete game;
		break;
	}
	case 3: // load
	{
		Game* game = new LoadMode;
		game->prepareToRun(runGame);
		if (runGame)
		{
			game->run();
		}
		delete game;
		break;
	}
	case 4: // silent
	{

		//_strategy = new SmartStrategy(_map);
		break;
	}
	}

}