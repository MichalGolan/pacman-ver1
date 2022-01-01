#include "SaveMode.h"

void SaveMode::runScreen(int& res)
{
	res = GO;
	int timer = 0, index = 0;
	char key = 0;
	try
	{
		setMap(index); //exception here
		_currScreen = getScreenName(*(_files.begin() + index));
	}
	catch (Exception& e)
	{
		_files.erase(_files.begin() + index); //remove current map name 
		throw e;
	}
	string stepsFile = _currScreen;
	ofstream steps(stepsFile.append(".steps"), ios_base::app);
	ofstream result(_currScreen.append(".result"), ios_base::app);

	do {
		if (_kbhit()) //only if new input in buffer
		{
			key = _getch();
			if (key == ESC)
			{
				pause(res);
			}
			else if (validMove(key))
			{
				_pacman.setDirection(getDirectionKey(key)); // extract the direction by 'key', and setting new direction accordingly //mimi
			}
		}
		if (timer % 2 == 0) //to make the ghost move 1/2 speed of pacman
		{
			for (auto g = _ghosts.begin(); g != _ghosts.end(); g++)
			{
				g->step(_pacman.getLocation());
				steps << "g" << g->getDirection() << " ";
			}
		}
		if (timer % 4 == 0) //to make the ghost move 1/4 speed of pacman
		{
			_fruit.step();
			if (_fruit.getisActive())
			{
				steps << "f" << "a" << _fruit.getFigure() << _fruit.getDirection() << _fruit.getLocation();
			}
			else
			{
				steps << "f" << "n" << " ";

			}
			timer = 0;
		}
		timer++;

		_pacman.step();
		steps << "p" << _pacman.getDirection() << " ";

		printByIndex(DATALINE);
		meetings();
		_pacman.move();

		Sleep(300);
		_pointsInTime++;
		endGameAndSaveRes(res, result);

	} while (res == GO);
	_files.erase(_files.begin() + index); //remove current map name 
	system("CLS");
	setTextColour(WHITE);

}

void SaveMode::endGameAndSaveRes(int& play, ofstream& result)
{
	if (_pacman.getBCscore() == _map->getMaxBC() || _lives == 0) // all breadcrumbs got eaten --> win game
	{
		if (_pacman.getBCscore() == _map->getMaxBC())
		{
			play = WIN;
			result << endl << _pointsInTime ;
		}
		else
		{
			play = LOSE;
			result << _pointsInTime << " ";
		}

	}
}
