#ifndef _MAP_H
	#define _MAP_H

#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <queue>
#include "QItem.h"
#include "Position.h"

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
    const vector<Position> getGhostlocVec() const;
    int                 getTotalBC() const;
    Position            getPacmanLocation() const;
    Position            getDataLine() const;

    int      isNextLocationWallorTunnel(const Position& nextLocation) const;

    int               shortestPathLen(Position dest, Position src) const;
    Position::compass getBestRoute(const Position &dest, const Position &src) const;
    Position::compass randDirection(const Position& currPos) const;

    Position isATunnel(const Position& pos) const;
    int isBorders(int row, int col) const {
        return ((row == _height - 1) || (col == _width - 1) || (row == 0) || (col == 0));
    }
    int isBorders(Position pos) const
    {
        return isBorders(pos.y, pos.x);
    }

private:
    int                 _width;  //coloumns --->
    int                 _height; //rows    |
                                   //      v
    mutable bool**      _visited;
    tileType**          _map;
    int                 _totalBC;
    static int          _colourfullMap;
    Position            _pacmanLocation, _dataLine;
    vector<Position>    _ghostsLocation;

    const int dataWidth = 20;
    const int dataHeight = 3;

    //private setters
    void        setVisited() const;
};


#endif
