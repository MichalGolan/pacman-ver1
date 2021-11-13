#include "Map.h"

Map::Map(const char** newMap) : _width(80), _height(25) //this function construts a new map. given a char array, 
                                                        //it 'translates' it to a tileType array
{
	_totalBC = 0;

    _map = new tileType * [_height];
    for (int i = 0; i < _height; i++)
    {
        _map[i] = new tileType[_width];
        for (int j = 0; j < _width; j++)
        {
            if (newMap[i][j] == typeKey[WALL]) // if it's a '#' meaning wall
                _map[i][j] = WALL;
            else
            {
				if (_width % 2 == 0) //breadcrumbs appear in the even coloumns, for aesthetic purposes :)
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

void Map::setTile(Position pos, int newtype)
{
    _map[pos.x][pos.y] = (tileType)newtype;
}

int Map::getTileType(Position pos)
{
    return (int)_map[pos.x][pos.y];
}

void Map::print()
{
	int i;
	for (i = 0; i < ROW; i++)
	{
		cout << _map[i] << endl;
	}
}
