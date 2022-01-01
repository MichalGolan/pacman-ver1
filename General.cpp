#include "General.h"
enum MODE { REG = 1, SAVE, LOAD, SILENT };
const char* modes[] = { "-save", "-load", "-silent" };

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

	for (unsigned int i = 0 ; i < fileNames.size() && !found ; ++i )
	{
		if (fileNames.at(i).ends_with(fname))
		{
			res = i;
			found = 1;
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

int checkValidMode(int argc, char* argv[])
{
	if (argc == 1) //no input --> regular game
	{
		return REG;
	}
	else
	{
		if (strcmp(argv[1], modes[1]) == 0) //input: load
		{
			if (argc == 2) //input: load silent
			{
				return LOAD;
			}
			else if(argc == 3 && strcmp(argv[2], modes[2]) == 0)
			{
				return SILENT;
			}
		}
		else if (strcmp(argv[1], modes[0]) == 0) //input: save
		{
			return SAVE;
		}
	}
	return 0;
}

string getScreenName(const string& name)
{
	int index = name.find_last_of('.');
	return name.substr(0,index);
}