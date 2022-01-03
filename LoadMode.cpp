#include "LoadMode.h"

void LoadMode::runScreen(int& res)
{
	res = GO;
	int timer = 0;
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
				g->stepByDir(newDir);
			}
		}
		if (timer % 4 == 0) //to make the ghost move 1/4 speed of pacman
		{
			//newDir = getStep(stepsFile);
			newDir = getStep(ss);
			if (newDir != Position::STAY)
			{
				_fruit.stepByDir(newDir);
			}
			timer = 0;
		}
		timer++;

		//newDir = getStep(stepsFile);
		newDir = getStep(ss);
		_pacman.loadStep(newDir);
		printByIndex(DATALINE);
		meetings();
		_pacman.move();

		Sleep(100);
		endGame(res);

	} while (res == GO);
	_files.erase(_files.begin()); //remove current map name 
	_stepsFiles.erase(_stepsFiles.begin());
	system("CLS");
}

void LoadMode::prepareToRun(int& runGame)
{
	getFiles(_files);
	if (!_files.size()) // no screen files in directory
	{
		printByIndex(NOFILES);
		runGame = 0;
	}
	for (auto& name : _files)
	{
		string stepFileName = getScreenName(name).append(".steps");
		_stepsFiles.push_back(stepFileName);
	}
}

void LoadMode::setMapForLoad()
{
	if (_map)
	{
		delete _map;
	}
	_map = new Map(_files.front()); //exception here

	updateCreaturesByMap();
	_map->print();
	printByIndex(DATALINE);
}

Position::compass LoadMode::getStep(stringstream& file) 
{
	string word;
	file >> word;
	if (word != "")
	{
		if (word.front() == 'f')
		{
			if (word.at(1) == 'n')
			{
				return Position::STAY;
			}
			else if (word.at(1) == 'f')
			{
				_fruit.setFigure(word.at(2));
				_fruit.setLocation(extractPos(word.substr(4)));
				return (Position::compass)(word.at(3) - '0');
			}
			else
			{
				return (Position::compass)(word.at(2) - '0');
			}
		}
		else
		{
			return (Position::compass)(word.at(1) - '0');
		}
	}
	else
	{
		return Position::STAY;
	}
}

Position LoadMode::extractPos(const string& pos)
{
	int x, y;
	char comma;
	stringstream ss(pos);
	ss >> x;
	ss >> comma;
	ss >> y;
	
	return Position( x,y );
}
