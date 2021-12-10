#include "Fruit.h"

Fruit::Fruit(Position::compass direction, char figure) : Creature(figure, direction), _appearTime(0)
{

}

void Fruit::randFigure()
{
	char figure = '0' + ((rand() % 5) + 5);   //rand -->  0, 1, 2, 3, 4 // rand + 5 --> 5, 6, 7, 8, 9, 
	setFigure(figure);
}

void Fruit::setAppearTime(int newTime)
{
	_appearTime = newTime;
}

int	 Fruit::getAppearTime() const
{
	return _appearTime;
}

//reset fruit
void Fruit::reset()
{
	randDirection();
	randFigure();
	//randLocation();
}