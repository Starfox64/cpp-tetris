#include "stdafx.h"
#include "Cell.h"


//	CONSTRUCTORS
Cell::Cell()
{
	this->y = 0;
	this->x = 0;
	this->color = 15;
}

Cell::Cell(int y, int x)
{
	this->y = y;
	this->x = x;
	this->color = 15;
}

Cell::Cell(int y, int innerY, int x, int innerX, int color)
{
	this->y = y;
	this->innerY = innerY;
	this->x = x;
	this->innerX = innerX;

	this->color = color;
}

Cell::~Cell()
{
}


//	GETTERS
int Cell::getX()
{
	return this->x;
}

int Cell::getY()
{
	return this->y;
}

int Cell::getInnerX()
{
	return this->innerX;
}

int Cell::getInnerY()
{
	return this->innerY;
}

int Cell::getColor()
{
	return this->color;
}


//	SETTERS
void Cell::setX(int x)
{
	this->x = x;
}

void Cell::setY(int y)
{
	this->y = y;
}

void Cell::setInnerX(int x)
{
	this->innerX = x;
}

void Cell::setInnerY(int y)
{
	this->innerY = y;
}

void Cell::setColor(int color)
{
	this->color = color;
}


//	OPERATOR OVERLOADS
std::ostream& operator<<(std::ostream& stream, const Cell* c)
{
	if (c == NULL)
		stream << "  ";
	else
	{
		utils::changeColor(c->color);
		stream << "[]";
		utils::changeColor(15);
	}
	return stream;
}