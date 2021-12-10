#include "Creature.h"

Creature::Creature(char figure, Position::compass direction) : _location({ 2,1 }), _colour(WHITE), _map(nullptr)
{
	setDirection(direction);
	setFigure(figure);
}

void Creature::setColour(Colour c) {
	_colour = c;
}

void Creature::setFigure(const char c) {
	_figure = c;
}

void Creature::setDirection(int dir) {
	_direction = (Position::compass)dir;
}

void Creature::setDirection(Position::compass dir) {
	_direction = dir;
}

void Creature::setLocation(Position newLocation) {
	_location = newLocation;
}

void Creature::setMap(Map& map)
{
	_map = &(map);
}

//calls for move of Position
void Creature::move()
{
	_location.move(_colour, _figure, _direction);
}

//return random direction
Position::compass Creature::randDirection()
{
	int dir = rand() % 4 ; //--> 0, 1, 2, 3
	setDirection(dir);
	return (Position::compass)dir;
}

Position Creature::getLocation() const
{
	return _location;
}

Position::compass Creature::getDirection() const
{
	return _direction;
}

// this function checks if next location is a wall or a tunnel, seperating cases by direction (if up or down, if left or down)
int Creature::isNextLocationWallorTunnel(Position::compass dir, Position nextLocation) const
{
	if (_map->getTileType(nextLocation) == Map::WALL) // a wall
	{
		return 1;
	}
	else if (_map->getTileType(nextLocation) == Map::TUNNEL) // tunnel
	{
		return 2;
	}
	else
	{
		return 0;
	}
}