#include"Game.h"

const int ESC = 27;
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

Game::Game()
{
	_breadcrumbs = 0;
	_lives = 3;
	_colourfulGame = 0;
}

void Game::initGhosts()
{
	_ghosts[0].setFigure('$');
	_ghosts[0].setLocation({ 1,78 });
	_ghosts[0].setDirection(1);
	_ghosts[1].setFigure('$');
	_ghosts[1].setLocation({ 18,2 });
	_ghosts[1].setDirection(3);
	if (!_colourfulGame)
	{
		_ghosts[0].setColour(WHITE);
		_ghosts[1].setColour(WHITE);
	}
	else
	{
		_ghosts[0].setColour(WHITE); // choose colour later *******************
		_ghosts[1].setColour(WHITE); // choose colour later *******************
	}
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
		run(); 
		// run ends when: 
		// 1. lives == 0
		// 2. score == total bread
		break;
	}
	case 8:
	{
		printInfo();
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
		if (_kbhit() ) //only if new inpur in buffer
		{
			key = _getch(); // add lowercase func *************
			if (validMove(key))
			{
				_pacman.setDirection(_pacman.getDirectionKey(key));     // extract the direction by 'key', and setting new direction accordingly
			}
		}
		if (timer % 2 == 0)
		{
			//move ghost ************************
			timer = 1;
		}
		timer++;
		handleNextMove();
		Sleep(1000);
	} while (key != ESC);

	//setTextColor(Color::WHITE);
	//clear_screen();
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

	if ((_pacman.getDirection() == 0 || _pacman.getDirection() == 1) && _map.getTileType(nextpos) == 1) // direction is up or down && a wall
	{
		_pacman.setDirection(4);
	}
	else if ((_pacman.getDirection() == 2 || _pacman.getDirection() == 3) && _map.getTileType(nextnextpos) == 1) // direction is left or right && a wall
	{
		_pacman.setDirection(4);
	}
	else if (_map.getTileType(nextpos) == 2) // not a wall --> check if BC
	{
			_map.setTile(nextpos, 0);
			_breadcrumbs++;
			_pacman.setLocation(nextpos);
	}
	else if (_map.getTileType(nextpos) == 0) // if empty
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


Position Game::getNextPos()
{
	Position curPos = _pacman.getLocation();
	int x = curPos.x;
	int y = curPos.y;
	
	switch (_pacman.getDirection())
	{
	case 0: // UP
		--y;
		break;
	case 1: // DOWN
		++y;
		break;
	case 2: // LEFT
		--x;
		break;
	case 3: // RIGHT
		++x;
		break;
	case 4: // STAY
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
	return (_pacman.getLocation().compare(_ghosts[0].getLocation()) && _pacman.getLocation().compare(_ghosts[1].getLocation()));
}

void Game::printMenu() const
{
	cout << "Welcome to the pacman!" << endl << "please press your choice:" << endl << "1 - start a new game" << endl <<
		"8 - Present instructionsand keys" << endl << "9 - EXIT" << endl;
}

void Game::pause()
{

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
		<< "Good Luck!" << endl;
}
