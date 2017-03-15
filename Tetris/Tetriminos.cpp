#include "stdafx.h"
#include "Tetriminos.h"

//	CONSTRUCTORS
Tetriminos::Tetriminos()
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		this->components[i] = new Cell(0, i+3);
	}
}

Tetriminos::~Tetriminos()
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		if (this->components[i] != NULL) this->components[i] = NULL;
	}
}

//	METHODS
int Tetriminos::top()
{
	int min = INT32_MAX;
	for (int i = 0; i < NB_CELLS; i++)
	{
		if (min > (*this)[i]->getY())
			min = (*this)[i]->getY();
	}
	return min;
}

int Tetriminos::bottom()
{
	int max = 0;
	for (int i = 0; i < NB_CELLS; i++)
	{
		if (max < (*this)[i]->getY())
			max = (*this)[i]->getY();
	}
	return max;
}

int Tetriminos::left()
{
	int min = INT32_MAX;
	for (int i = 0; i < NB_CELLS; i++)
	{
		if (min >(*this)[i]->getX())
			min = (*this)[i]->getX();
	}
	return min;
}

int Tetriminos::right()
{
	int max = 0;
	for (int i = 0; i < NB_CELLS; i++)
	{
		if (max < (*this)[i]->getX())
			max = (*this)[i]->getX();
	}
	return max;
}

bool Tetriminos::contains(Cell* c)
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		if ((*this)[i] == c)
			return true;
	}
	return false;
}


//	OPERATOR OVERLOADS
Cell* Tetriminos::operator[](unsigned int index)
{
	if (index < NB_CELLS) return this->components[index];
	return NULL;
}

Tetriminos* Tetriminos::operator+=(int y)
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		(*this)[i]->setY(
			(*this)[i]->getY() + y
		);
	}

	return this;
}

Tetriminos* Tetriminos::operator-=(int x)
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		this->components[i]->setX(
			this->components[i]->getX() + x
		);
	}
	
	return this;
}