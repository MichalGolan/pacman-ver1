#ifndef _MAP_H
	#define _MAP_H

#include <iostream>
#include "Position.h"

using namespace std;

const int maxHeight = 25;
const int maxWidth = 80;

const int defHeight = 19;
const int defWidth = 76;

class Map
{
public:
    //                0      1       2         3       4              5
    enum tileType { EMPTY, WALL, BREADCRUMB, GHOST, PACMAN, GHOSTandBREADCRUMB };
    const char typeKey[3] = { ' ', '#', '.' };

public:
    Map();//char** newMap, int width, int height);
    ~Map();
    void print();
    
    void       setTile(Position pos, tileType newtype);
    tileType   getTileType(Position pos) const; //check how to return the enum and not index

private:
    int         _width;  //coloumns --->
    int         _height; //rows    |
                        //        v
    tileType**  _map;
    int         _totalBC;
};


#endif
