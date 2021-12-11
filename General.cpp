#include "General.h"

int numOfLinesinFile(ifstream& file)
{
	string line;
	int res = 0;
	while (getline(file, line))
	{
		++res;
	}
	file.clear();
	file.seekg(0);
	return res;
}

int findInVector(const vector<string>& fileNames, const string& fname)
{
	int found = 0, res = -1;

	for (int i = 0 ; i < fileNames.size() && !found ; ++i )
	{
		if (fileNames.at(i) == fname)
		{
			res = i;
		}
	}
	return res;
}

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


void setTextColour(Colour colourToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colourToSet);
}

//lowercase a given character or leave it as it is if it's not a letter
void lower(char& ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		ch = ch + ('a' - 'A');
	}
}

int randinRange(int topRange, int botRange)
{
	return (rand() % (topRange-botRange)) + botRange;
}