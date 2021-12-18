#include "Map.h"

int Map::_colourfullMap = 0;

Map::Map(const string& fname) 
{
    createFromFile(fname);
}

Map::~Map()
{
    if (_map) //if a map was created, free memory
    {
        for (int i = 0; i < _height + (dataHeight - 1); i++)
        {
            delete[] _map[i];
            delete[] _visited[i];
        }
        delete[] _map;
        delete[] _visited;
    }
}

void Map::translateScreen(const string& fileName)
{
    ifstream file(fileName);

    string curFileLine;

    if (file.is_open())
    {
        _height = numOfLinesinFile(file);
        _map = new tileType * [_height + (dataHeight - 1)]; // for the case in which the dataline is at the end and we need more lines for it

        unsigned int i;

        for (i = 0; i < _height; i++)
        {
            getline(file, curFileLine);
            if (i == 0)
            {
                handleFirstLine(curFileLine);
            }

            _map[i] = new tileType[_width];
            translate(curFileLine, _map[i], i);
        }

        for (i; i < _height + (dataHeight - 1); i++)
        {
            _map[i] = new tileType[_width];
            for (int j = 0; j < _width; j++)
            {
                _map[i][j] = EMPTY;
            }
        }
    }
    file.close();
    clearDataLine();
}

void Map::translate(const string& line, tileType* mapLine, int curLine)
{
    int j = 0;
    for (j = 0; j < _width; j++)
    {
        if (j >= line.size()) //if my current line is shorter than the width, then the rest of it is empty-->breadcrumb'd
        {
            mapLine[j] = EMPTY;
        }
        else
        {
            if (line.at(j) == typeKey[WALL]) // if it's a '#' meaning wall
            {
                mapLine[j] = WALL;
            }

            else if (line.at(j) == ' ' || line[j] == '@' || line[j] == '$')
            {
                if (isBorders(curLine, j))
                {
                    mapLine[j] = TUNNEL;
                }
                else
                {
                    mapLine[j] = BREADCRUMB;
                    _totalBC++;

                    if (line[j] == '@')
                    {
                        _pacmanLocation.setXY(j, curLine);
                    }
                    else if (line[j] == '$')
                    {
                        _ghostsLocation.push_back(Position(j, curLine));
                    }
                }
            }
            else if (line.at(j) == '&')
            {
                _dataLine.setXY(j, curLine);
                mapLine[j] = EMPTY;
            }

            else if (line.at(j) == '%')
            {
                mapLine[j] = EMPTY;
            }
        }
    }

}


void Map::clearDataLine()
{
    if (_dataLine.y >= _height - (dataHeight - 1))
    {
        _height += (dataHeight - (_height - _dataLine.y));
    }

    for (unsigned int i = 0; i < dataHeight; i++)
    {
        for (int j = 0; j < dataWidth; j++)
        {
            int row = _dataLine.y + i;
            int col = _dataLine.x + j;
            if (_map[_dataLine.y + i][_dataLine.x + j] == BREADCRUMB)
            {
                _totalBC--;
            }
            _map[_dataLine.y + i][_dataLine.x + j] = EMPTY; //clearing the space for our dataline in its designated borders
        }
    }
}

void Map::handleFirstLine(const string& fileLine)
{
    _width = fileLine.size();

    size_t found = fileLine.find("&");
    if (found != string::npos)
    {
        if (found + 1 + dataWidth > _width) //this means dataline will make our screen wider because it needs 20 chars in width
        {
            _width = found + dataWidth;
        }
    }
}

void Map::createFromFile(const string& fileName)
{
    _totalBC = 0;
    _colourfullMap = 0;

    translateScreen(fileName);

    _visited = new bool* [_height + (dataHeight - 1)];
    for (int i = 0; i < _height + (dataHeight - 1); i++)
    {
        _visited[i] = new bool[_width];
    }

    setVisited();
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
    system("cls");
    gotoxy(0, 0);
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

Position Map::getGhostsLoc(int i) const
{
    return _ghostsLocation.at(i);
}

const vector<Position> Map::getGhostlocVec() const
{
    return _ghostsLocation;
}

int Map::getTotalBC() const
{
    return _totalBC;
}

Position Map::getPacmanLocation() const
{
    return _pacmanLocation;
}

Position Map::getDataLine() const
{
    return _dataLine;
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
            {
                setVisited();
                return curr.getDistance();
            }

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

Position::compass Map::getBestRoute(const Position &dest, const Position &src) const
{
    int currBestPath = shortestPathLen(dest, src);

    if (currBestPath == -1)
    {
        return randDirection(src); // gives some random route in case there is no way to get to the destination at all
    }

    else
    {
        vector<int> paths;
        vector<Position::compass> routes;
        
        int upPath, downPath, leftPath, rightPath, min = currBestPath;
        Position::compass bestDir = Position::UP;

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
            if (paths.at(i) < min)
            {
                bestDir = routes.at(i);
                min = paths.at(i);
            }
        }

        return bestDir; //return the direction of which gave us the minimal route to the destination
    }
}


Position::compass Map::randDirection(const Position& currPos) const
{
    array<Position::compass, 4> dirs{ Position::compass::UP, Position::compass::DOWN, Position::compass::LEFT, Position::compass::RIGHT };
    unsigned scrambler = chrono::system_clock::now().time_since_epoch().count();

    shuffle(dirs.begin(), dirs.end(), default_random_engine(scrambler));

    Position NextGhostloc;
    int i = 0, found = 0;
    while (i < 4 && !found)
    {
        NextGhostloc = currPos;
        NextGhostloc.update(dirs[i]);
        if (isNextLocationWallorTunnel(NextGhostloc))
        {
            i++;
        }
        else
        {
            found = 1;
        }
    }
    if (!found)
    {
        return Position::compass::STAY;
    }
    else
    {
        return dirs[i];
    }
}


//checks for a tunnel on the other side
Position Map::isATunnel(const Position& pos) const
{
    if (pos.y == 0 && (getTileType(pos.x, getHeight() - 1) == Map::TUNNEL || getTileType(pos.x, getHeight() - 1) != Map:: WALL))
    {
        return { pos.x, getHeight() - 1 };
    }
    if (pos.y == getHeight() - 1 && (getTileType(pos.x, 0) == Map::TUNNEL || getTileType(pos.x, 0) != Map::WALL))
    {
        return  { pos.x, 0 };
    }
    if (pos.x == 0 && (getTileType(getWidth() - 1, pos.y) == Map::TUNNEL|| getTileType(getWidth() - 1, pos.y) != Map::WALL))
    {
        return { getWidth() - 1, pos.y };
    }
    if (pos.x == getWidth() - 1 && (getTileType(0, pos.y) == Map::TUNNEL || getTileType(0, pos.y) != Map::WALL))
    {
        return { 0, pos.y };
    }
    return pos;
}

// this function checks if next location is a wall or a tunnel, seperating cases by direction (if up or down, if left or down)
int Map::isNextLocationWallorTunnel(const Position& nextLocation) const
{
    if (getTileType(nextLocation) == Map::WALL) // a wall
    {
        return 1;
    }
    else if (isBorders(nextLocation) || getTileType(nextLocation) == Map::TUNNEL)// tunnel / borders
    {
        return 2;
    }
    
    else
    {
        return 0;
    }
}