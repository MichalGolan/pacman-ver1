#ifndef _EXCEPTIONS_H
	#define _EXCEPTIONS_H

#include <iostream>
#include <string>

using namespace std;

class Exception
{
public:
	Exception(const char* str) : _thrownException(str) {}

	virtual void show() const { cout << "Error: " << _thrownException << endl; }

private:
	const char* _thrownException;
};




#endif
