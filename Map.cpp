#include "Map.h"

Map::Map() : _width(defWidth), _height(defHeight), _totalBC(0) //empty constructor
                                                               //this function construts a new map. given a char array, 
                                                               //it 'translates' it to a tileType array
{
    char staticMap[19][76] = { {"#############################+++++++++#####################################"},
{"+ . . . . . . . . . . # . . . . . . . . . . . . . . # . . . . . . . . . . +"},
{"+ . ############### . # . ####################### . # . ############### . +"},
{"+ . # . . . . . . . . . . . . . . . . . . . . . # . # . . . . . . . . . . +"},
{"# . # . ########### . ##### . ############### . # . # . ##### . ####### . #"},
{"# . # . . . . . . . . # . . . . . . . . . . . . . . . . . . . . # . . . . #"},
{"# . . . ########### . # . ######### . ####### . ############# . # . ### . #"},
{"# . # . . . . . . # . # . # . . . . . . . . # . # . . . . . . . # . . . . #"},
{"# . # . ####### . # . # . ################### . # . ############# . ### . #"},
{"# . # . # . . . . . . # . . . . . . . . . . . . # . . . . . . . . . . # . #"},
{"# . # . ########### . . . ############### . # . # . ############### . . . #"},
{"# . . . . . . . . . . # . . . . . . . . . . # . . . . . . . . . . . . # . #"},
{"# . # . ########### . ######### . ########### . ############# . ####### . #"},
{"# . # . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . . . #"},
{"+ . ### . # . ############################### . # . ##### . ########### . #"},
{"+ . . . . # . # . . . . . . . . . . . . . . . . # . . . . . . . . . . . . #"},
{"+ . ### . # . # . ########################### . # . ################### . #"},
{"# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #"},
{"#############################+++++++++#####################################"} };

    char** myMap = new char* [19];
    for (int i = 0; i < 19; i++)
    {
        myMap[i] = new char[76];
        strcpy(myMap[i], staticMap[i]);
    }

    _map = new tileType * [_height];
    for (int i = 0; i < _height; i++)
    {
        _map[i] = new tileType[_width];
        for (int j = 0; j < _width; j++)
        {
            if (myMap[i][j] == typeKey[WALL]) // if it's a '#' meaning wall
                _map[i][j] = WALL;

            else if (myMap[i][j] == '+')
            {
                _map[i][j] = TUNNEL;
            }
            else
            {
                if (j % 2 == 0) //breadcrumbs appear in the even coloumns, for aesthetic purposes :)
                {
                    _map[i][j] = BREADCRUMB;
                    _totalBC++;
                }
                else
                    _map[i][j] = EMPTY;
            }
        }
    }
    setCorners();
}

Map::~Map()
{
    if (_width != -1) //otherwise this would mean the program did not make a dynaic array for map.
    {
        for (int i = 0; i < _height; i++)
        {
            delete[] _map[i];
        }
        delete[] _map;
    }
}

void Map::setTile(Position pos, tileType newtype)
{
    _map[pos.y][pos.x] = newtype;
}

Map::tileType Map::getTileType(Position pos) const
{
    return _map[pos.y][pos.x];
}

Map::tileType Map::getTileType(int _x, int _y) const
{
    return _map[_y][_x];
}

void Map::print() const
{
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            cout << typeKey[_map[i][j]];
        }
        cout << endl;
    }
}

void Map::printTile(Position pos) const
{
    int x = pos.x;
    int y = pos.y;
    gotoxy(x, y);
    cout << typeKey[_map[y][x]];
}

Position Map::getCorner(int index) const
{
    return _corners[index];
}

int Map::getMaxBC() const
{
    return _totalBC;
}
int Map::getWidth() const
{
    return _width;
}

int Map::getHeight() const
{ 
    return _height; 
}


void Map::setCorners()
{
    //(coloumn, row)
    _corners[0].setXY(2, 1); //upper left
    _corners[1].setXY(_width - 4, 1); //upper right
    _corners[2].setXY(2, _height - 2); //lower left
    _corners[3].setXY(_width - 4, _height - 2); //lower right
}

