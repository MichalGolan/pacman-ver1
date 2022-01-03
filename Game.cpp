#include"Game.h"

//game's constructor
Game::Game() : _lives(3), _colourfulGame(0), _map(nullptr), _difficulty(1)
{
	setArrowKeys("wxads"); 
}

Game::~Game()
{
	delete _map;
}

int Game::askForDifficulty()
{
	char index;
	do
	{
		cout << "How easy do you want the game to be?" << endl;
		cout << "1 - child friendly level" << endl << "2 - i'm not as good as I think I am" << endl << "3 - BRING IT ON!" << endl;
		cin >> index;
		system("cls");
		if (!((index - '0') >= 1   &&   (index - '0') <= 3)) // not between 1 <= index <= 3
		{
			printByIndex(INVALID);
		}
	} while (!((index - '0') >= 1 && (index - '0') <= 3));
	return (index - '0');
}

//if the player chose a colourful game will handle accordingly
void Game::colourIt()
{
	if (_colourfulGame)
	{
		_pacman.setColour(YELLOW);
		_fruit.setColour(RED);
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
	_ghosts.clear();
	for (auto& gLoc : _map->getGhostlocVec())
	{
		_ghosts.push_back(Ghost(gLoc));
	}
	for (auto& g : _ghosts)
	{
		g.setMap(_map);
		g.setStrategy(_difficulty);
	}
}

void Game::setMap(int& index)
{
	if (_map)
	{
		delete _map;
	}
	index = askForFile(_files);

	_map = new Map(_files.at(index)); //exception here

	updateCreaturesByMap();
	colourIt();
	_map->print();
	printByIndex(DATALINE);
}

//handling user choice and running or exiting
void Game::set(int & runGame)
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
		prepareToRun(runGame);
		if (runGame)
		{
			run();
		}
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
		runGame = FINISHED;
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
	sort(screenFiles.begin(), screenFiles.end());
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

	int index = -1;
	while (index == -1 && c == 'y')
	{	
		string fname;	
		cout << "Please enter file name that ends with .screen:" << endl;
		cin >> fname;
		system("cls");
		index = findInVector(fileNames, fname);
		if (index == -1)
		{
			printByIndex(INVALID);
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
		}
	}
	if (index >= 0)			// found index in vector for file
		return index;
	else					// finish loop with 'n' --> regular file order starts with 0
		return 0;  
}

void Game::prepareToRun(int& runGame)
{
	system("CLS");
	_colourfulGame = askForColours();
	
	system("CLS");
	_difficulty = askForDifficulty();

	getFiles(_files);
	if (!_files.size()) // no screen files in directory
	{
		printByIndex(NOFILES);
		runGame = 0;
	}
}

void Game::runScreen(int& res)
{
	res = GO;
	int timer = 0, index = 0;
	char key = 0;
	try
	{
		setMap(index); //exception here
	}
	catch (Exception& e)
	{
		_files.erase(_files.begin() + index); //remove current map name 
		throw e;
	}
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
			}
		}
		if (timer % 4 == 0) //to make the ghost move 1/4 speed of pacman
		{
			_fruit.step();
			timer = 0;
		}
		timer++;

		_pacman.step();
		printByIndex(DATALINE);
		meetings();
		_pacman.move(); 

		Sleep(300);

		endGame(res);

	} while (res == GO);
	_files.erase(_files.begin() + index); //remove current map name 
	system("CLS");
	setTextColour(WHITE);
}

//RUNS THE GAME!!!
void Game::run()
{
	int play = GO;
	while ((play == GO || play == WIN ) && _files.size()) // loop run while none of these accured: no more screens, game lost (play changed to 0), player chose to exit
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
	printByIndex(play);
}

void Game::updateCreaturesByMap()
{
	_pacman.setMap(_map);
	_pacman.setLocation(_map->getPacmanLocation());
	_fruit.setMap(_map);
	initGhosts();
	_pacman.reset();
	_pacman.resetScore();
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
	if (_fruit.getisActive())
	{
		_fruit.reset();
	}
}

int Game::meetings()
{
	int pacmanDied = pacmanGhostMeet();
	if(!pacmanDied)
	{
		if (_pacman.handleFruitMeet(_fruit.getLocation(), _fruit.getFigure(), _fruit.getisActive()))
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
	return pacmanDied;
}

//checks if pacman and ghost collided
int Game::pacmanGhostMeet()
{
	int pacmanDied = 0;
	for (auto g = _ghosts.begin()  ;  !pacmanDied && g != _ghosts.end()  ;   g++)
	{
		if (_pacman.getLocation() == g->getLocation())
		{
			_lives--;
			resetCreatures(); // ---- this function eill call for a restart function for each creature
			pacmanDied = 1;
		}
	}
	return pacmanDied;
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
		cout << "GAME OVER. you've lost all your lives." << endl;
		cout << "Press any key to continue" << endl;
		fflush(stdin);
		getch();
		fflush(stdin);
		break;
	}
	case 1: // user pressed ESC
	{
		gotoxy(_map->getDataLine().x, _map->getDataLine().y); // data line
		cout << " Game paused -" << endl;
		gotoxy(_map->getDataLine().x, _map->getDataLine().y + 1);
		cout << " ESC to continue " << endl;
		gotoxy(_map->getDataLine().x, _map->getDataLine().y + 2);
		cout << " ENTER to quit game";
		break;
	}
	case WIN: // game won
	{
		cout << "YOU WIN! YOU DA BEST" << endl; 
		cout << "Press any key to continue" << endl;
		fflush(stdin);
		getch();
		fflush(stdin);
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
		_map->printEmptyDataLine();
		gotoxy(_map->getDataLine().x, _map->getDataLine().y); // data line
		cout << " Score: " << _pacman.getBCscore() + _pacman.getBonusPoints() << endl;
		gotoxy(_map->getDataLine().x, _map->getDataLine().y + 1);
		cout << " Lives: " << _lives;
		gotoxy(_map->getDataLine().x, _map->getDataLine().y + 2);
		cout << " press ESC to Pause ";
		break;
	}
	case INVALID:
	{
		cout << "Invalid input, please try again." << endl << endl;
		break;
	}
	case NOFILES:
	{
		cout << "No screen files found in Directory." << endl;
		break;
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
} 

void Game::setArrowKeys(const char* keys) { // "waxd s"
	_arrowKeys[0] = keys[0];
	_arrowKeys[1] = keys[1];
	_arrowKeys[2] = keys[2];
	_arrowKeys[3] = keys[3];
	_arrowKeys[4] = keys[4];
} 
