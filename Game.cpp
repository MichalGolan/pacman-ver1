#include"Game.h"

const int ESC = 27;
const int ENTER = 13;
//Map _map;
//Pacman _pacman;
//Ghost _ghosts[2];
//int breadcrumbs;
//int lives;
/*
Position _location;
int _direction;
char _figure;
Colour _colour;
*/

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
	
	Ghost ghost1({ 1,78 }, Position::DOWN, '$', wantedColour);
	Ghost ghost2({ 18,2 }, Position::RIGHT, '$', wantedColour);

	_ghosts[0] = ghost1; //will use ghost's copy constructor
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

	//get input for moves for pacman
	//initialize movments both pacman and ghost
	int timer = 1;
	char key = 0;
	do {
		//print pacman and ghosts - always or only if location changed?
		//if  printing always might create a sort of "blinking" of the figure, if the location is the same

		if (_kbhit() ) //only if new input in buffer
		{
			key = _getch(); // add lowercase func *************
			if (key == ESC)
			{
				key = pause();
			}
			else if (validMove(key))
			{
				_pacman.setDirection(_pacman.getDirectionKey(key));     // extract the direction by 'key', and setting new direction accordingly
			}
		}
		if (timer % 2 == 0) //to make the ghost move 1/2 speed of pacman
		{
			//move+print ghost ************************
			timer = 1;
		}
		timer++;
		handleNextMove();
		Sleep(1000);
	} while (key != ENTER); //this needs to change! exiting this loop is for QUITTING THE GAME! 
	                      //NOT FOR PAUSE!
	//pause function should occur in the scope of this loop. when entering it,
	//it will "pause" the loop and therefore the run function until we finish it. 
	//
	//inside the pause - a while loop waiting for esc or some EXIT key to be chosen
	//
	//if ESC hit, the while inside pause will stop. 
	//we will return to the 'run' while loop with some flag to know that we need to continue, 
	//and will to continue as we were. (as stacking function works...)
	//
	//if EXIT key will be chose we will return with a flag that we need to finish the game,
	//the while loop in run will catch that and we will exit the while loop therefore exiting the 'run'
	//therefore going back to game menu that alled for run... :)

	//setTextColor(Color::WHITE);
	system("CLS");
}

int Game::validMove(char key) // is input ok?
{
	if (_pacman.getDirectionKey(key) != -1)
	{
		return 1;
	}
	return 0;
}

// this function check what to on the next move according to: if a wall, a breadcrumb or a ghost. it considers up down or left right
// it takes into consideration the case #_@_# where it not allowed to move left or right
	
void Game::handleNextMove()
{
	Position nextpos = getNextPos();
	Position nextnextpos = getNextNextPos();

	if ((_pacman.getDirection() == Position::UP || _pacman.getDirection() == Position::DOWN) && _map.getTileType(nextpos) == Map::WALL) // direction is up or down && a wall
	{
		_pacman.setDirection(Position::STAY);
	}
	else if ((_pacman.getDirection() == Position::LEFT || _pacman.getDirection() == Position::RIGHT) && _map.getTileType(nextnextpos) == Map::WALL) // direction is left or right && a wall
	{
		_pacman.setDirection(Position::STAY);
	}
	else if (_map.getTileType(nextpos) == Map::BREADCRUMB) // not a wall --> check if BC
	{
			_map.setTile(nextpos, Map::EMPTY);
			_breadcrumbs++;
			_pacman.setLocation(nextpos);
	}
	else if (_map.getTileType(nextpos) == Map::EMPTY) // if empty
	{
		_pacman.setLocation(nextpos);
	}
	if (pacmanGhostMeet())// check if pacman and ghost collide 
	{
		//handle boom
	}

}

/*
* if up or down
*		check wall or BC for nextposition
*		if wall 
*		update dir to stay
*		else 
*		check BC
* 
* else if left or right 
*		handle:
*		check double move for wall
*		update direction to stay
*		else
*		check for BC
* 
* anyway check ghost on pacman




*/





	//if wall -- > change to stay direction
	//if bc --> update score, update map from BREADCRUMB to EMPTY
	//if ghost --> restart board(include restart location of pacman (1 1) and init for ghost), live--


Position Game::getNextPos() //why is this function in game and not in pacman?
{
	Position curPos = _pacman.getLocation();
	int x = curPos.x;
	int y = curPos.y;
	
	switch (_pacman.getDirection())
	{
	case Position::UP:
		--y;
		break;
	case Position::DOWN:
		++y;
		break;
	case Position::LEFT:
		--x;
		break;
	case Position::RIGHT:
		++x;
		break;
	case Position::STAY:
		break;
	}
	curPos.setXY(x, y);
	return curPos;
}

Position Game::getNextNextPos()
{
	Position curPos = _pacman.getLocation();
	int x = curPos.x;
	int y = curPos.y;

	switch (_pacman.getDirection())
	{
	case 2: // LEFT
		x -= 2;
		break;
	case 3: // RIGHT
		x += 2;
		break;
	}
	curPos.setXY(x, y);
	return curPos;
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

char Game::pause()
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
		gotoxy(defHeight, 0);
		for (int i = 0; i < 57; i++)
		{
			cout << " ";
		}
	}

	return input;
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
