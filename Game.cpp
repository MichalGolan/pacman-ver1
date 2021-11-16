#include"Game.h"

const int ESC = 27;
const int ENTER = 13;

Game::Game() : _breadcrumbs(0), _lives(3), _colourfulGame(0)
{
	initGhosts();
}

void Game::initGhosts()
{
	Colour wantedColour;

	if (!_colourfulGame)
	{
		wantedColour = WHITE;
	}
	else
	{
		wantedColour = WHITE; // choose colour later *******************
	}
	
	Ghost ghost1(_map.getCorner(1), Position::DOWN, '1', wantedColour);
	Ghost ghost2(_map.getCorner(2), Position::RIGHT, '2', wantedColour);

	_ghosts[0] = ghost1; 
	_ghosts[1] = ghost2; 
}


void Game::set(int &play)
{
	int choice;

	printMenu();
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		// ask for colours? update data member colourful game
		system("CLS");
		run(); 
		// run ends when: 
		// 1. lives == 0
		// 2. score == total bread
		// 3. when user press enter during pause
		
		break;
	}
	case 8:
	{
		printInfo();
		getch();
		system("CLS");
		break;
	}
	case 9:
	{
		cout << "Bye" << endl;
		play = 0;
		break;
	}
	default:
		break;
	}
}

void Game::run()
{
	_map.print();
	//print game data --> function --> Score: 000     Game: on!          Lives: 03
	//initialize movments both pacman and ghost
	int timer = 0, play = 1;
	char key = 0;
	do {
		//if  printing always might create a sort of "blinking" of the figure, if the location is the same
		_pacman.move();
		if (_kbhit() ) //only if new input in buffer
		{
			key = _getch(); 
			if (key == ESC)
			{
				pause(play);
			}
			else if (validMove(key))
			{
				_pacman.setDirection(_pacman.getDirectionKey(key));     // extract the direction by 'key', and setting new direction accordingly
			}
		}
		if (timer % 2 == 0) //to make the ghost move 1/2 speed of pacman
		{
			handleGhostMove();
			timer = 0;
		}
		timer++;
		handlePacmanMove();
		Sleep(1000);
		endGame(play);
	} while (play == 1); 
	// print messeage according to play
	//setTextColor(Color::WHITE);
	system("CLS");
}

int Game::validMove(char& key) // is input ok?
{
	lower(key);
	if (_pacman.getDirectionKey(key) != -1)
	{
		return 1;
	}
	return 0;
}

int Game::isNextLocationWall(Position::compass dir, Position location)
{
	if ((dir == Position::UP || dir == Position::DOWN) && _map.getTileType(location) == Map::WALL) // direction is up or down && a wall
	{
		return 1;
	}
	location.update(dir);// getting 2 steps from original location, usefull for left/right movement
	if ((dir == Position::LEFT || dir == Position::RIGHT) && _map.getTileType(location) == Map::WALL) // direction is left or right && a wall
	{
		return 1;
	}
	return 0;
}


// this function check what to on the next move according to: if a wall, a breadcrumb or a ghost. it considers up down or left right
// it takes into consideration the case #_@_# where it not allowed to move left or right
void Game::handlePacmanMove()
{
	Position nextpos = _pacman.getLocation();
	nextpos.update(_pacman.getDirection());

	if (isNextLocationWall(_pacman.getDirection(), nextpos))
	{
		_pacman.setDirection(Position::STAY);
	}
	else if (_map.getTileType(nextpos) == Map::BREADCRUMB) // not a wall --> check if BC
	{
		_map.setTile(nextpos, Map::EMPTY);
		_breadcrumbs++;
	}
	if (pacmanGhostMeet())// check if pacman and ghost collide 
	{
		//handle boom
	}

}
//if ghost --> restart board(include restart location of pacman (1 1) and init for ghost), live--


void Game::handleGhostMove()
{
	for (Ghost& g : _ghosts)
	{
		Position Ghostloc = g.getLocation();
		Position NextGhostloc = g.getLocation(); ///// -------------- find another solution

		NextGhostloc.update(g.getDirection());

		if (isNextLocationWall(g.getDirection(), NextGhostloc))
		{
			g.switchDirection();
		}

		g.move();

		gotoxy(Ghostloc.x, Ghostloc.y);
		_map.printTile(Ghostloc);
	}
}


int Game::pacmanGhostMeet()
{
	return ((_pacman.getLocation() ==_ghosts[0].getLocation()) || (_pacman.getLocation()==_ghosts[1].getLocation()));
}

void Game::printMenu() const
{
	cout << "Welcome to the pacman!" << endl << "please press your choice:" << endl << "1 - start a new game" << endl <<
		"8 - Present instructions and keys" << endl << "9 - EXIT" << endl;
}

void Game::pause(int & play)
{
	char input = 1;
	printPause();
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
		gotoxy(0, defHeight + 2);
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

void Game::endGame(int& play)
{
	if (_breadcrumbs == _map.getMaxBC()) // all breadcrumbs got eaten --> win game
	{
		play = 2;
	}
	else if (_lives == 0)
	{
		play = 0;
	}
}


void Game::printPause()
{
	gotoxy(0, defHeight + 2);
	cout << "game paused, press ESC to continue or ENTER to quit game" << endl;
}

void Game::printInfo()
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

}
