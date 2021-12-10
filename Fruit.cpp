#include "Fruit.h"

Fruit::Fruit(Position::compass direction, char figure) : Creature(figure, direction)
{
	randDirection();
	randFigure();
}

void Fruit::randFigure()
{
	char figure = '0' + ((rand() % 5) + 5);   //rand -->  0, 1, 2, 3, 4 // rand + 5 --> 5, 6, 7, 8, 9, 
	setFigure(figure);
}