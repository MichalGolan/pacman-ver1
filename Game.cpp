#include"Game.h"

//game's constructor
Game::Game() : _breadcrumbs(0), _lives(3), _colourfulGame(0)
{
	initGhosts();
	setArrowKeys("wxads"); // mimi

}

//if the player chose a colourful game will handle accordingly
void Game::colourIt()
{
	if (_colourfulGame)
	{
		_pacman.setColour(YELLOW);
		_ghosts[0].setColour(LIGHTMAGENTA);
		_ghosts[1].setColour(LIGHTCYAN);
		_map.setColourfulMap(_colourfulGame);
	}
}

//sets the ghosts of the game
void Game::initGhosts()
{	
	Ghost ghost1(_map.getCorner(1), Position::DOWN, '$');
	Ghost ghost2(_map.getCorner(2), Position::RIGHT, '$');

	_ghosts[0] = ghost1; 
	_ghosts[1] = ghost2; 
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
		system("CLS");
		_colourfulGame = askForColours();
		colourIt();
		run(); 
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
int Game::askForColours()
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

//RUNS THE GAME!!!
void Game::run()
{
	_map.print();
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
			handleGhostMove();
			timer = 0;
		}
		timer++;

		handlePacmanMove();
		_pacman.move();
		Sleep(300); 

		endGame(play);

	} while (play == GO); 

	system("CLS");
}

//checks if the key is a valid move key
int Game::validMove(char& key)
{
	lower(key);
	if (getDirectionKey(key) != -1) //mimi
	{
		return 1;
	}
	return 0;
}

// this function checks if next location is a wall or a tunnel, seperating cases by direction (if up or down, if left or down)
int Game::isNextLocationWallorTunnel(Position::compass dir, Position nextLocation) const
{
	if ((dir == Position::UP || dir == Position::DOWN)) // direction is up or down
	{
		if (_map.getTileType(nextLocation) == Map::WALL) // a wall
		{
			return 1;
		}
		else if (_map.getTileType(nextLocation) == Map::TUNNEL) // tunnel
		{
			return 2;
		}
	}
	nextLocation.update(dir);// getting 2 steps from original location, usefull for left/right movement

	if ((dir == Position::LEFT || dir == Position::RIGHT)) // direction is left or right 
	{
		if (_map.getTileType(nextLocation) == Map::WALL) // a wall
		{
			return 1;
		}
		else if (_map.getTileType(nextLocation) == Map::TUNNEL) // tunnel
		{
			return 2;
		}
	}
	return 0;
}


// this function checks what is the next move according to: if a wall, a breadcrumb, a tunnel or a ghost. 
// it considers directions
void Game::handlePacmanMove()
{
	Position nextpos = _pacman.getLocation();
	nextpos.update(_pacman.getDirection());
	int wallorTunnel = isNextLocationWallorTunnel(_pacman.getDirection(), nextpos);

	if (wallorTunnel == 2)  // tunnel
	{
		handleTunnel(nextpos); 
	}
	else if (wallorTunnel == 1 || notAPath()) //wall or not a path
	{
		_pacman.setDirection(Position::STAY);
	}
	else if (_map.getTileType(nextpos) == Map::BREADCRUMB) // not a wall --> check if BC
	{
		_map.setTile(nextpos, Map::EMPTY);
		_breadcrumbs++;
		printByIndex(DATALINE);
	}
	if (pacmanGhostMeet())// check if pacman and ghost collide 
	{
		_lives--;
		resetCreatures();
		printByIndex(DATALINE);
	}
}

//handling the movement for a tunnel
void Game::handleTunnel(Position pos) 
{
	Position newPos = isATunnel(pos);
	if (newPos == pos)
	{
		_pacman.setDirection(Position::STAY);
	}
	else
	{
		_map.printTile(_pacman.getLocation());
		_pacman.setLocation(newPos);
	}
}

//checks for a tunnel on the other side
Position Game::isATunnel(Position pos) const
{
	if (pos.y == 0 && _map.getTileType(pos.x, _map.getHeight() - 1) == Map::TUNNEL) 
	{
		return { pos.x, _map.getHeight() - 1};
	}
	if (pos.y == _map.getHeight() - 1 && _map.getTileType(pos.x, 0) == Map::TUNNEL)
	{
		return  { pos.x, 0 };
	}
	if (pos.x == 1 && _map.getTileType(_map.getWidth() - 2, pos.y) == Map::TUNNEL)
	{
		return { _map.getWidth() - 3, pos.y };
	}	
	if (pos.x ==  _map.getWidth() - 3 && _map.getTileType(0 , pos.y) == Map::TUNNEL)
	{
		return { 1, pos.y };
	}
	return pos;
}

//puts creatures back in their starting locations
void Game::resetCreatures()
{
	_map.printTile(_pacman.getLocation());
	_map.printTile(_ghosts[0].getLocation());
	_map.printTile(_ghosts[1].getLocation());

	_pacman.setLocation(_map.getCorner(0));
	_ghosts[0].setLocation(_map.getCorner(1));
	_ghosts[1].setLocation(_map.getCorner(2));
	
	_pacman.setDirection(Position::STAY);
}

// if movement is vertical and location coloumn not even
// meaning not a legitimate path (#_._#)	
int Game::notAPath() const
{
	Position::compass dir = _pacman.getDirection();
	
	if ((dir == Position::UP || dir == Position::DOWN) && _pacman.getLocation().x % 2 != 0) 
	{
		return 1;
	}
	return 0;
}

//responsible for visual and logical ghost movement
void Game::handleGhostMove()
{
	for (Ghost& g : _ghosts)
	{
		Position Ghostloc = g.getLocation();
		Position NextGhostloc = g.getLocation();

		NextGhostloc.update(g.getDirection());

		if (isNextLocationWallorTunnel(g.getDirection(), NextGhostloc))
		{
			g.switchDirection();
		}
		g.move();
		_map.printTile(Ghostloc);
	}
}

void Game::smartGhostMove()
{
	Position currPacman = _pacman.getLocation();

	for (Ghost& g : _ghosts)
	{
		Position Ghostloc = g.getLocation();

		Position::compass newDir = _map.getBestRoute(currPacman, Ghostloc);
		g.setDirection(newDir);

		g.move();
		_map.printTile(Ghostloc);
	}
}

//checks if pacman and ghost collided
int Game::pacmanGhostMeet()
{
	return ((_pacman.getLocation() ==_ghosts[0].getLocation()) || (_pacman.getLocation()==_ghosts[1].getLocation()));
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
		gotoxy(0, _map.getHeight() + 2);
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
	if (_breadcrumbs == _map.getMaxBC() || _lives == 0) // all breadcrumbs got eaten --> win game
	{
		if (_breadcrumbs == _map.getMaxBC())
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
		gotoxy(0, _map.getHeight() + 2); //go to message line
		cout << "GAME OVER. you've lost all your lives." << endl;
		break;
	}
	case 1: // user pressed ESC
	{
		gotoxy(0, _map.getHeight() + 2); //go to message line
		cout << "game paused, press ESC to continue or ENTER to quit game" << endl;
		break;
	}
	case WIN: // game won
	{
		gotoxy(0, _map.getHeight() + 2); //go to message line
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
		gotoxy(0, _map.getHeight() + 1); // data line
		cout << "score: " << _breadcrumbs << " | " << "Lives: " << _lives;
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
} // mimi
