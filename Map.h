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
    //                0      1       2      
    enum tileType { EMPTY, WALL, BREADCRUMB };
    const char typeKey[3] = { ' ', '#', '.' };

public:
    Map();//char** newMap, int width, int height);
    ~Map();
    void print();
    void printTile(Position pos);

    void       setTile(Position pos, tileType newtype);
    tileType   getTileType(Position pos) const; //check how to return the enum and not index
    Position   getCorner(int index) const;
    int        getMaxBC() const;
private:
    int         _width;  //coloumns --->
    int         _height; //rows    |
                        //        v
    tileType**  _map;
    int         _totalBC;
    Position    _corners[4];

    void        setCorners();

};


#endif
