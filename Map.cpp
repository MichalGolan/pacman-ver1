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
    
    _visited = new bool* [_height];
    _map = new tileType * [_height];
    for (int i = 0; i < _height; i++)
    {
        _visited = new bool* [_width];
        _map[i] = new tileType[_width];
        for (int j = 0; j < _width; j++)
        {
            if (myMap[i][j] == typeKey[WALL]) // if it's a '#' meaning wall
            {
                _map[i][j] = WALL;
            }
    
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

    setVisited();
    setCorners();
}

Map::~Map()
{
        for (int i = 0; i < _height; i++)
        {
            delete[] _map[i];
            delete[] _visited[i];
        }
        delete[] _map;
        delete[] _visited;
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

void Map::setVisited() const // sets the visited array to its default - walls and tunnels are inaccessible
                             // to creatures (except pacman) hence they are marked by default as 'visited'
{
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            if (_map[i][j] == WALL || _map[i][j] == TUNNEL)
            {
               _visited[i][j] = true;
            }
            else
            {
                _visited[i][j] = false;
            }
        }
    }
}

int Map::shortestPathLen(Position dest, Position src) const
{
    if (src.y >= 0 && src.y < _height && src.x >= 0 && src.x < _width) // only if the src given is inside borders go ahead
    {
        _visited[src.y][src.x] = true;

        QItem source(src.y, src.x, 0);

        queue<QItem> pathsToCheck;

        pathsToCheck.push(source);

        while (!pathsToCheck.empty())
        {
            QItem curr = pathsToCheck.front();
            int cRow = curr.getRow();
            int cCol = curr.getCol();
            int cDist = curr.getDistance();
            pathsToCheck.pop();


            if (dest == Position(cCol, cRow)) // if we have reached our destination, return the path
                return curr.getDistance();

            if (cRow - 1 >= 0 && !_visited[cRow - 1][cCol]) // checking for upwards if not outside borders & not visited 
            {
                pathsToCheck.push(QItem(cRow - 1, cCol, cDist++));
                _visited[cRow - 1][cCol] = true;
            }

            if (cCol - 1 >= 0 && !_visited[cRow][cCol - 1]) // checking for left if not outside borders & not visited 
            {
                pathsToCheck.push(QItem(cRow, cCol - 1, cDist++));
                _visited[cRow][cCol - 1] = true;
            }

            if (cRow + 1 < _height && !_visited[cRow + 1][cCol]) // checking for downwards if not outside borders & not visited 
            {
                pathsToCheck.push(QItem(cRow + 1, cCol, cDist++));
                _visited[cRow + 1][cCol] = true;
            }

            if (cCol + 1 < _width && !_visited[cRow][cCol + 1]) // checking for right if not outside borders & not visited 
            {
                pathsToCheck.push(QItem(cRow, cCol + 1, cDist++));
                _visited[cRow][cCol + 1] = true;
            }
        }
    }
    setVisited();
    return -1; // if not found a path!
}

Position::compass Map::getBestRoute(Position &dest, Position &src) const
{
    int currBestPath = shortestPathLen(dest, src);

    if (currBestPath == -1)
    {
        return randRoute(src); // gives some random route in case there is no way to get to the destination at all
    }

    else
    {
        vector<int> paths;
        vector<Position::compass> routes;
        
        int upPath, downPath, leftPath, rightPath, min;

        Position::compass bestDir;

        upPath = shortestPathLen(dest, Position(src.y - 1, src.x));
        downPath = shortestPathLen(dest, Position(src.y + 1, src.x));
        leftPath = shortestPathLen(dest, Position(src.y, src.x - 1));
        rightPath = shortestPathLen(dest, Position(src.y, src.x + 1));

        if (upPath != -1)
        {
            paths.push_back(upPath);
            routes.push_back(Position::UP);
        }
        if (downPath != -1)
        {
            paths.push_back(downPath);
            routes.push_back(Position::DOWN);
        }
        if (leftPath != -1)
        {
            paths.push_back(leftPath);
            routes.push_back(Position::LEFT);
        }
        if (rightPath != -1)
        {
            paths.push_back(rightPath);
            routes.push_back(Position::RIGHT);
        }

        for (int i = 0; i < paths.size(); ++i) // find the path which is better than the current best (minimal)
        {
            if (paths.at(i) < currBestPath)
            {
                bestDir = routes.at(i);
                min = paths.at(i);
            }
        }

        return bestDir; //return the direction of which gave us the minimal route to the destination
    }
}

