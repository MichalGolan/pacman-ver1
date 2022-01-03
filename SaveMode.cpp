#include "SaveMode.h"

void SaveMode::runScreen(int& res)
{
	res = GO;
	int timer = 0, index = 0, pacmanDied;
	char key = 0;
	string output;
	stringstream ss(output);
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
	steps.flush();
	result.flush();

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
				ss << "g" << g->getDirection() << " ";
			}
		}
		if (timer % 4 == 0) //to make the ghost move 1/4 speed of pacman
		{
			_fruit.stepSave(steps, ss);
			timer = 0;
		}
		timer++;

		steps << "p" << _pacman.getDirection() << " ";
		ss << "p" << _pacman.getDirection() << " ";
		_pacman.step();

		printByIndex(DATALINE);
		pacmanDied = meetings();
		if (pacmanDied)
		{
			result << _pointsInTime << " ";
		}
		_pacman.move();

		Sleep(300);
		_pointsInTime++;
		endGameAndSaveRes(res, result);

	} while (res == GO);
	int stringsize = ss.str().size();
	_files.erase(_files.begin() + index); //remove current map name 
	_pointsInTime = 0;
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
			result << endl << _pointsInTime;
		}
		else
		{
			play = LOSE;
		}
	}
}
