#ifndef _MAP_H
	#define _MAP_H

#include <iostream>
#include "Position.h"

using namespace std;

const int ROW = 21;
const int COL = 80;

class Map
{
    //                0      1       2         3       4              5
    enum tileType { EMPTY, WALL, BREADCRUMB, GHOST, PACMAN, GHOSTandBREADCRUMB };
    const char typeKey[3] = { ' ', '#', '.' };
    const int _width;  //coloumns --->
    const int _height; //rows    |
                       //        v
    tileType** _map;

    int _totalBC;

public:
    Map();
    Map(const char** newMap);   //problematic... I can get a faulty map! :( 
    void print();
    
    void setTile(Position pos, int newtype);
    int getTileType(Position pos); //check how to return the enum and not index
};


#endif
