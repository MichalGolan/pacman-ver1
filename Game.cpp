#include"Game.h"

void Game::setGame()
{
	int choice;
	printMenu();
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
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
		exit(0);
		break;
	}
	default:
		break;
	}
}
void Game::printMenu()
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
		<< "LEFT a or A" << endl		<< "RIGHT d or D" << endl		<< "UP w or W" << endl		<< "Down x or X" << endl		<< "STAY s or S" << endl << endl
		<< "To Pause, press ESC at any time" << endl << endl
		<< "Your Goal: eat all the breadcrumbs, avoid all the ghosts!" << endl
		<< "Once a ghost hits you, you lose a life. Once you lose all your lives it is GAME OVER!" << endl
		<< "Good Luck!" << endl;
}
