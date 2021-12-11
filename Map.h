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
    Map(const string& fname);
    ~Map();

    //files
    void createFromFile(const string& fileName);
    void translate(const string& line, tileType* mapLine, int curLine);
    void translateScreen(const string& fileName);
    void handleFirstLine(const string& fileLine);
    void clearDataLine();

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
    int                 getMaxBC() const;
    int                 getWidth() const;
    int                 getHeight() const;
    Position            getGhostsLoc(int i) const;
    int                 getTotalBC() const;
    Position            getPacmanLocation() const;
    Position            getDataLine() const;



    int               shortestPathLen(Position dest, Position src) const;
    Position::compass getBestRoute(const Position &dest, const Position &src) const;
    Position isATunnel(const Position& pos) const;
    int isBorders(int row, int col) {
        return (row == _height - 1) || (col == _width - 1) || (row == 0) || (col == 0);
    }

private:
    int                 _width;  //coloumns --->
    int                 _height; //rows    |
                                   //      v
    mutable bool**      _visited;
    tileType**          _map;
    int                 _totalBC, _colourfullMap;
    Position            _pacmanLocation, _dataLine, _corners[4];
    vector<Position>    _ghostsLocation;

    const int dataWidth = 20;
    const int dataHeight = 3;

    //private setters
    void        setVisited() const;
};


#endif
