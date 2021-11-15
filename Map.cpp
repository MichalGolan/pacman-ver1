#include "Map.h"

Map::Map() : _width(defWidth), _height(defHeight), _totalBC(0) //empty constructor
                                                    //this function construts a new map. given a char array, 
                                                    //it 'translates' it to a tileType array
{
    char staticMap[19][76] = { {"###########################################################################"},
    {"#                     #                             #                     #"},{"#   ###############   #   #######################   #   ###############   #"},
    {"#   #                                           #   #                     #"},{"#   #   ###########   #####   ###############   #   #   #####   #######   #"},
    {"#   #                 #                                         #         #"},{"#       ###########   #   #########   #######   #############   #   ###   #"},
    {"#   #             #   #   #                 #   #               #         #"},{"#   #   #######   #   #   ###################   #   #############   ###   #"},
    {"#   #   #             #                         #                     #   #"},{"#   #   ###########       ###############   #   #   ###############       #"},
    {"#                     #                     #                         #   #"},{"#   #   ###########   #########   ###########   #############   #######   #"},
    {"#   #                                                       #             #"},{"#   ###   #   ###############################   #   #####   ###########   #"},
    {"#         #   #                                 #                         #"},{"#   ###   #   #   ###########################   #   ###################   #"},
    {"#                                                                         #"},{"###########################################################################"} };

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
    _map[pos.x][pos.y] = newtype;
}

Map::tileType Map::getTileType(Position pos) const
{
    return _map[pos.x][pos.y];
}

void Map::print()
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
