#include "Map.h"

Map::Map() : _width(defWidth), _height(defHeight), _totalBC(0), _colourfullMap(0)     //empty constructor
                                                                                      //this function construts a new map. given a char array, 
                                                                                      //it 'translates' it to a tileType array
{
    char staticMap[19][76] = { 
    {"#############################+++++++++#####################################"},
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
        for (int i = 0; i < _height; i++)
        {
            delete[] _map[i];
        }
        delete[] _map;
}

void Map::setColourfulMap(int flag)
{
    _colourfullMap = flag;
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

//prints the entire board - only happens once during a game
void Map::print() const
{
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            setTileColour(i, j);
            cout << typeKey[_map[i][j]];
        }
        cout << endl;
    }
}

//sets colour according to the tileType (if colourful game!)
void Map::setTileColour(int i, int j) const
{ 
    if (_colourfullMap && _map[i][j] == WALL)
    {
        setTextColour(BLUE);
    }
    else if (_colourfullMap && _map[i][j] == BREADCRUMB)
    {
        setTextColour(BROWN);
    }
}

//prints a given coordinate according to the board
void Map::printTile(Position pos) const
{
    int x = pos.x;
    int y = pos.y;
    setTileColour(y, x);
    gotoxy(x, y);
    cout << typeKey[_map[y][x]];
}

//returns corner by index
// 0-topleft, 1-topright, 2-botleft, 3-botright
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

//sets corners according to the constructed map
void Map::setCorners()
{
    //(coloumn, row)
    _corners[0].setXY(2, 1); //upper left
    _corners[1].setXY(_width - 4, 1); //upper right
    _corners[2].setXY(2, _height - 2); //lower left
    _corners[3].setXY(_width - 4, _height - 2); //lower right
}

