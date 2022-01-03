#include "Menu.h"

int main(int argc, char* argv[])
{
	if (int mode = checkValidMode(argc, argv))
	{
		start(mode);
	}
	else
	{
		cout << "Usage: [-save] [-load] [-load -silent]" << endl;
	}

}

/*
addition to readMe:
* out format to steps file --> numbers represnts directions 
* 
*/