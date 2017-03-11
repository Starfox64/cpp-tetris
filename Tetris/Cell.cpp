#include "stdafx.h"
#include "Cell.h"


//	CONSTRUCTORS
Cell::Cell()
{
	this->y = 0;
	this->x = 0;
	this->falling = true;
}

Cell::Cell(int y, int x)
{
	this->y = y;
	this->x = x;
	this->falling = true;
}

Cell::Cell(int y, int x, bool falling)
{
	this->y = y;
	this->x = x;
	this->falling = falling;
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

bool Cell::isFalling()
{
	return this->falling;
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

void Cell::setFalling(bool falling)
{
	this->falling = falling;
}


//	OPERATOR OVERLOADS
std::ostream& operator<<(std::ostream& stream, const Cell* c)
{
	if (c == NULL)
		stream << "  ";
	else
		stream << "[]";
	return stream;
}