﻿#include"Game.h"

//game's constructor
Game::Game() : _lives(3), _colourfulGame(0)
{
	initGhosts();
	setArrowKeys("wxads"); // mimi

}

Game::~Game()
{
	delete _map;
}

//if the player chose a colourful game will handle accordingly
void Game::colourIt()
{
	if (_colourfulGame)
	{
		_pacman.setColour(YELLOW);
		for (auto& g : _ghosts)
		{
			g.setColour(LIGHTCYAN);
		}
		_map->setColourfulMap(_colourfulGame);
	}
}
//sets the ghosts of the game
void Game::initGhosts()
{	
	for (auto& gLoc : _map->getGhostsLoc())
	{
		_ghosts.push_back(Ghost(gLoc));
	}
}

//handling user choice and running or exiting
void Game::set(int &play)
{
	char c;
	printByIndex(MENU);
	fflush(stdin);
	cin >> c;
	int choice = c - '0';

	switch (choice)
	{
	case 1:
	{
		prepareToRun();
		/*system("CLS");
		_colourfulGame = askForColours();
		colourIt();
		system("CLS");

		run(); */
		break;
	}
	case 8:
	{
		printByIndex(choice); // print information and instructions
		getch();
		system("CLS");
		break;
	}
	case 9:
	{
		cout << "Bye" << endl;
		play = LOSE;
		break;
	}
	default:
		printByIndex(INVALID);
		break;
	}
}

//ask for colours with input validation
int Game::askForColours() const
{
	char c;
	do
	{
		cout << "Would you like to play with colours?" << endl << "Y - Yes / N - No" << endl;
		cin >> c;
		lower(c);
		system("cls");
		if (c != 'y' && c != 'n')
		{
			printByIndex(INVALID);
		}
	} while (c != 'y' && c != 'n');

	if (c == 'y')
	{
		return 1;
	}
	return 0;
}


void Game::getFiles(vector<string>& screenFiles)
{
	for (const auto& entry : fs::directory_iterator("."))
	{
		if (entry.path().string().ends_with("screen")) {
			screenFiles.push_back(entry.path().string());
		}
	}
}

int Game::askForFile(const vector<string>& fileNames ) const // ---------------> to move to menu class!!!!!
{
	char c;
	do
	{
		cout << "Would you like to choose specific board?" << endl << "Y - Yes / N - No" << endl;
		cin >> c;
		lower(c);
		system("cls");
		if (c != 'y' && c != 'n')
		{
			printByIndex(INVALID);
		}
	} while (c != 'y' && c != 'n');

	if (c == 'y')
	{
		string fname;	
		int index = -1;

		cout << "Please enter file name that ends with .screen:" << endl;
		cin >> fname;
		system("cls");
		while (index == -1)
		{
			cin >> fname;
			index = findInVector(fileNames, fname);
			if (index == -1)
			{
				printByIndex(INVALID);
			}
		}
		return index;
	}
	return 0; //pressed no --> regular file order
}

void Game::prepareToRun()
{
	system("CLS");
	_colourfulGame = askForColours();
	colourIt();
	system("CLS");

	getFiles(_files);
	int index = askForFile(_files);
	_map = new Map(_files.at(index)); 
	updateCreaturesByMap();

	run();
}
//RUNS THE GAME!!!
void Game::run()
{
	_map->print();
	printByIndex(DATALINE);

	int timer = 0, play = GO;
	char key = 0;

	do {
		if (_kbhit() ) //only if new input in buffer
		{
			key = _getch(); 
			if (key == ESC)
			{
				pause(play);
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
				g->step();
			}
			timer = 0;
		}
		timer++;

		_pacman.step();
		printByIndex(DATALINE);
		meetings();
		_pacman.move(); // -------------> check later maybe to move this call into _pacman.step()
		Sleep(300); 

		endGame(play);

	} while (play == GO); 
	/// <summary>
	/// wrap the WHILE loop in a bigger loop while play == go
	/// change the inner loop to be for specific screen of the game --> we dont want to start over if the player won specific screen,
	///  but only when lost (no more lives) or won (finished all boardes)
	/// 
	/// therfore the current exicting loop need a condition change
	/// do not forget to delete map
	/// and load a new map if needed
	/// </summary>
	system("CLS");
}

void Game::updateCreaturesByMap()
{
	_pacman.setMap(_map);
	_pacman.setLocation(_map->getPacmanLocation());
	_fruit.setMap(_map);
	int i = 0;
	for (auto& g : _ghosts)
	{
		g.setMap(_map);
		g.setLocation(_map->getGhostsLoc(i));
		++i;
	}
}


//checks if the key is a valid move key
int Game::validMove(char& key)
{
	lower(key);
	if (getDirectionKey(key) != -1) 
	{
		return 1;
	}
	return 0;
}


//puts creatures back in their starting locations
void Game::resetCreatures() 
{
	_pacman.reset();
	for (auto g = _ghosts.begin(); g != _ghosts.end(); g++)
	{
		g->reset();
	}
	_fruit.reset();
	
}

void Game::meetings()
{
	pacmanGhostMeet();
	if(_pacman.handleFruitMeet(_fruit.getLocation(), _fruit.getFigure()))
	{
		_fruit.reset();
	}
	for (auto& g : _ghosts)
	{
		if (g.getLocation() == _fruit.getLocation())
		{
			_fruit.reset();
		}
	}
}

//checks if pacman and ghost collided
void Game::pacmanGhostMeet()
{
	int flag = 1;
	for (auto g = _ghosts.begin()  ;  flag && g != _ghosts.end()  ;   g++)
	{
		if (_pacman.getLocation() == g->getLocation())
		{
			_lives--;
			resetCreatures(); // ---- this function eill call for a restart function for each creature
			printByIndex(DATALINE);
			flag = 0;
		}
	}
	
}

//pauses the game
//gives the user an option to exit the game from this window
void Game::pause(int & play)
{
	char input = 1;
	printByIndex(1);
	fflush(stdin);
	do
	{
		if (_kbhit()) //only if new input in buffer
		{
			input = _getch();
		}
	} while (input != ESC && input != ENTER);
	if (input == ESC)
	{
		gotoxy(0, _map->getHeight() + 2);
		for (int i = 0; i < 57; i++)
		{
			cout << " ";
		}
	}
	else
	{
		play = 3;
	}
}

//this function checks for win or loss and handles it
void Game::endGame(int& play)
{
	char c;
	if (_pacman.getBCscore() == _map->getMaxBC() || _lives == 0) // all breadcrumbs got eaten --> win game
	{
		if (_pacman.getBCscore() == _map->getMaxBC())
		{
			play = WIN;
		}
		else
		{
			play = LOSE;
		}
		printByIndex(play);
		cout << "Press any key to continue" << endl;
		fflush(stdin);
		getch();
		fflush(stdin);
	}	
}

//printing function for all kinds of printing during the game

void Game::printByIndex(int index) const
{
	setTextColour(WHITE);
	switch (index)
	{
	case LOSE: // game over
	{
		gotoxy(0, _map->getHeight() + 2); //go to message line
		cout << "GAME OVER. you've lost all your lives." << endl;
		break;
	}
	case 1: // user pressed ESC
	{
		gotoxy(0, _map->getHeight() + 2); //go to message line
		cout << "game paused, press ESC to continue or ENTER to quit game" << endl;
		break;
	}
	case WIN: // game won
	{
		gotoxy(0, _map->getHeight() + 2); //go to message line
		cout << "YOU WIN! YOU DA BEST" << endl; 
		break;
	}
	case 8: // info and instructions
	{
		cout << "Pacman game instructions:" << endl
			<< "Keys:" << endl
			<< "LEFT a or A" << endl
			<< "RIGHT d or D" << endl
			<< "UP w or W" << endl
			<< "Down x or X" << endl
			<< "STAY s or S" << endl << endl
			<< "To Pause, press ESC at any time" << endl << endl
			<< "Your Goal: eat all the breadcrumbs, avoid all the ghosts!" << endl
			<< "Once a ghost hits you, you lose a life. Once you lose all your lives it is GAME OVER!" << endl
			<< "Good Luck!" << endl << endl
			<< "Press any key to continue:" << endl;
		break;
	}
	case MENU:
	{
		cout << "Welcome to the pacman!" << endl << "please press your choice:" << endl << "1 - start a new game" << endl <<
			"8 - Present instructions and keys" << endl << "9 - EXIT" << endl;
		break;
	}
	case DATALINE:
	{
		gotoxy(0, _map->getHeight() + 1); // data line
		cout << "score: " << _pacman.getBCscore() + _pacman.getBonusPoints() << " | " << "Lives: " << _lives;
		break;
	}
	case INVALID:
	{
		cout << "Invalid input, please try again." << endl << endl;
	}
	default:
		break;
	}
}

//returns the direction by given key according to our arrow keys
int Game::getDirectionKey(char key) const 
{
	for (int i = 0; i < 5; i++)
	{
		if (key == _arrowKeys[i])
			return i;
	}
	return -1;
} //mimi

void Game::setArrowKeys(const char* keys) { // "waxd s"
	_arrowKeys[0] = keys[0];
	_arrowKeys[1] = keys[1];
	_arrowKeys[2] = keys[2];
	_arrowKeys[3] = keys[3];
	_arrowKeys[4] = keys[4];
} 
