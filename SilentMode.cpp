#include "SilentMode.h"

void SilentMode::runScreen(int& res)
{
	res = GO;
	int timer = 0, pacmanDied;
	char key = 0;
	try
	{
		setMapForLoad(); //exception here
	}
	catch (Exception& e)
	{
		_files.erase(_files.begin()); //remove current map name 
		throw e;
	}
	ifstream stepsFile(_stepsFiles.front());
	if (stepsFile.fail())
	{
		throw Exception("No steps file in directory");
	}
	string stepsFromFile;
	getline(stepsFile, stepsFromFile);
	stepsFile.close();
	stringstream ss(stepsFromFile);
	Position::compass newDir;
	;	do {
		if (timer % 2 == 0) //to make the ghost move 1/2 speed of pacman
		{
			for (auto g = _ghosts.begin(); g != _ghosts.end(); g++)
			{
				//newDir = getStep(stepsFile);
				newDir = getStep(ss);
				g->silentStepByDir(newDir);
			}
		}
		if (timer % 4 == 0) //to make the ghost move 1/4 speed of pacman
		{
			//newDir = getStep(stepsFile);
			newDir = getStep(ss);
			if (newDir != Position::STAY)
			{
				_fruit.silentStepByDir(newDir);
			}
			timer = 0;
		}
		timer++;

		//newDir = getStep(stepsFile);
		newDir = getStep(ss);
		_pacman.loadStep(newDir);

		pacmanDied = meetings();
		if (pacmanDied)
		{
			_pointOfLose.push_back(_pointsInTime);
		}
		_pacman.silentMove();
		_pointsInTime++;
		silentEndGame(res);

	} while (res == GO);
	compareToRes();
	_pointsInTime = 0;
	_files.erase(_files.begin()); //remove current map name 
	_stepsFiles.erase(_stepsFiles.begin());
	_resultsFile.erase(_resultsFile.begin());
}

void SilentMode::prepareToRun(int& runGame)
{
	LoadMode::prepareToRun(runGame);
	for (auto& name : _files)
	{
		string resFileName = getScreenName(name).append(".result");
		_resultsFile.push_back(resFileName);
	}
}


void SilentMode::silentEndGame(int& play)
{
	if (_pacman.getBCscore() == _map->getMaxBC() || _lives == 0) // all breadcrumbs got eaten --> win game
	{
		if (_pacman.getBCscore() == _map->getMaxBC())
		{
			play = WIN;
			_victory = _pointsInTime;
		}
		else
		{
			play = LOSE;
		}
	}
}

void SilentMode::compareToRes()
{
	int point, index = 0, equal = 1;
	ifstream resFile(_resultsFile.front());
	if (resFile.fail())
	{
		throw Exception("No result file in directory");
	}
	vector<int> pointsFromFile;
	string line;
	getline(resFile, line);
	istringstream ss(line);
	while (ss >> point)
	{
		pointsFromFile.push_back(point);
	}
	if (pointsFromFile.size() == _pointOfLose.size())
	{
		for (int i = 0; i < pointsFromFile.size() && equal; ++i)
		{
			if (pointsFromFile.at(i) != _pointOfLose.at(i))
			{
				equal = 0;
			}
		}
	}
	else
	{
		equal = 0;
	}
	point = -1;
	if (equal && (resFile >> point || _victory))
	{
		if (point != _victory)
		{
			equal = 0;
		}
	}
	if (equal)
	{
		_tests.push_back(getScreenName(_resultsFile.front()) + ": Test passed!\n");
	}
	else
	{
		_tests.push_back(getScreenName(_resultsFile.front()) + ": Test Failed :(\n");
	}
	_victory = 0;
	_pointOfLose.clear();
}

void SilentMode::silentRun()
{
	int play = GO;
	while ((play == GO || play == WIN) && _files.size()) // loop run while none of these accured: no more screens, game lost (play changed to 0), player chose to exit
	{
		try
		{
			runScreen(play);
		}
		catch (Exception& e)
		{
			system("cls");
			e.show();
			throw Exception("Error");
		}
	}
	system("cls");
	for (auto& t : _tests)
	{
		cout << t;
	}
}