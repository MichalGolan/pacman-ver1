#ifndef _MAP_H
	#define _MAP_H

#include <iostream>
#include <queue>
#include "QItem.h"
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
    Map();
    ~Map();

    //printers
    void print() const;
    void printTile(Position pos) const;

    //setters
    void       setColourfulMap(int flag);
    void       setTileColour(int i, int j) const;
    void       setTile(Position pos, tileType newtype);

    //getters
    tileType            getTileType(Position pos) const;
    tileType            getTileType(int _x, int _y) const;
    Position            getCorner(int index) const;
    int                 getMaxBC() const;
    int                 getWidth() const;
    int                 getHeight() const;
    vector<Position>    getGhostsLoc() const;

    int               shortestPathLen(Position dest, Position src) const;
    Position::compass getBestRoute(const Position &dest, const Position &src) const;
    Position isATunnel(const Position& pos) const;


private:
    int                 _width;  //coloumns --->
    int                 _height; //rows    |
                                   //      v
    mutable bool**      _visited;
    tileType**          _map;
    int                 _totalBC, _colourfullMap;
    Position            _pacmanLocation, _dataLine, _corners[4];
    vector<Position>    _ghostsLocation;


    //private setters
    void        setCorners();
    void        setVisited() const;
};


#endif
