#include "Creature.h"

Creature::Creature(char figure, Position::compass direction) : _location({ -1,-1 }), _colour(WHITE), _map(nullptr) //mimi
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

void Creature::setLocation(const Position& newLocation) {
	_location = newLocation;
}

void Creature::setMap(Map* map)
{
	_map = map;
}


void Creature::stepByDir(Position::compass dir)
{
	Position prevPos = _location;
	_direction = dir;
	move();
	_map->printTile(prevPos);

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

char Creature::getFigure() const
{
	return _figure;
}

