#include "Menu.h"

int main(int argc, char* argv[])
{
	if (int mode = checkValidMode(argc, argv))
	{
		start(mode);
	}
	//printer(usage);

}

/*
addition to readMe:
* out format to steps file --> numbers represnts directions 
* 
*/