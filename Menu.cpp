#include "Menu.h"

void start(int mode)
{
	int runGame = GO;
	Game* game = nullptr;
	try
	{
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
			game = new SaveMode;
			game->set(runGame);
			delete game;
			break;
		}
		case 3: // load
		{
			game = new LoadMode;
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
			game = new SilentMode;
			game->prepareToRun(runGame);
			if (runGame)
			{
				SilentMode* g = dynamic_cast<SilentMode*>(game);
				g->silentRun();
			}
			delete game;
			break;
		}
		}

	}
	catch (Exception&) 
	{
		delete game;
	}
}