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
    //                0      1       2         3
    enum tileType { EMPTY, WALL, BREADCRUMB, TUNNEL};
    const char typeKey[4] = { ' ', '#', '.', ' '};

public:
    //c'tor and d'tor
    Map();//char** newMap, int width, int height);
    ~Map();

    //printers
    void print() const;
    void printTile(Position pos) const;

    //setters
    void       setColourfulMap(int flag);
    void       setTileColour(int i, int j) const;
    void       setTile(Position pos, tileType newtype);

    //getters
    tileType   getTileType(Position pos) const;
    tileType   getTileType(int _x, int _y) const;
    Position   getCorner(int index) const;
    int        getMaxBC() const;
    int        getWidth() const;
    int        getHeight() const;

private:
    int         _width;  //coloumns --->
    int         _height; //rows    |
                         //        v
    tileType**  _map;
    int         _totalBC;
    Position    _corners[4];
    int         _colourfullMap;

    //private setter
    void        setCorners();
};


#endif
