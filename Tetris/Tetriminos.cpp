#include "stdafx.h"
#include "Tetriminos.h"

//	CONSTRUCTORS
Tetriminos::Tetriminos()
{
	int color = 11;
	for (int i = 0; i < NB_CELLS; i++)
		this->components[i] = new Cell(0, 1, i+3, i, color);
	this->maxExtent = 4;
	setNavPoint(-1, 3);
}

Tetriminos::Tetriminos(int i)
{
	switch (i)
	{
	case 0://I
		for (int i = 0; i < NB_CELLS; i++)
			this->components[i] = new Cell(0, 1, i+3, i, 11);
		maxExtent = 4;
		setNavPoint(-1, 3);
		break;
	case 1://O
		for (int i = 0; i < 2; i++)
			this->components[i] = new Cell(0, 0, i + 4, i, 8);
		for (int i = 2; i < 4; i++)
			this->components[i] = new Cell(1, 1, i + 2, i - 2, 8);
		maxExtent = 2;
		setNavPoint(0, 4);
		break;
	case 2://L
		this->components[3] = new Cell(0, 0, 5, 2, 14);
		for (int i = 0; i < 3; i++)
			this->components[i] = new Cell(1, 1, 3 + i, i, 14);
		maxExtent = 3;
		setNavPoint(0, 3);
		break;
	case 3://J
		this->components[3] = new Cell(0, 0, 3, 0, 9);
		for (int i = 0; i < 3; i++)
			this->components[i] = new Cell(1, 1, 3 + i, i, 9);
		maxExtent = 3;
		setNavPoint(0, 3);
		break;
	case 4://Z
		for (int i = 0; i < 2; i++)
			this->components[i] = new Cell(0, 0, i + 3, i, 12);
		for (int i = 2; i < 4; i++)
			this->components[i] = new Cell(1, 1, i + 2, i - 1, 12);
		maxExtent = 3;
		setNavPoint(0, 3);
		break;
	case 5://S
		for (int i = 0; i < 2; i++)
			this->components[i] = new Cell(0, 1, i + 4, i + 1, 10);
		for (int i = 2; i < 4; i++)
			this->components[i] = new Cell(1, 2, i + 1, i - 2, 10);
		maxExtent = 3;
		setNavPoint(-1, 3);
		break;
	case 6://T
		this->components[3] = new Cell(0, 0, 4, 1, 13);
		for (int i = 0; i < 3; i++)
			this->components[i] = new Cell(1, 1, 3 + i, i, 13);
		maxExtent = 3;
		setNavPoint(0, 3);
		break;
	}
}

Tetriminos::~Tetriminos()
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		if (this->components[i] != NULL) this->components[i] = NULL;
	}
}


//	GETTERS
Cell*** Tetriminos::getInnerBoard()
{
	Cell*** table = new Cell**[4];
	for (int i = 0; i < 4; i++)
	{
		table[i] = new Cell*[4];
		for (int j = 0; j < 4; j++)
			table[i][j] = NULL;
	}

	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
	{
		table[(*this)[i]->getInnerY()][(*this)[i]->getInnerX()] = (*this)[i];
	}

	return table;
}


//	METHODS
void Tetriminos::setNavPoint(int y, int x)
{
	navX = x;
	navY = y;
}

void Tetriminos::movNavPoint(int y, int x)
{
	navX += x;
	navY += y;
}

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

int** Tetriminos::getRotation()
{
	int** newPos = 0;// {y; innerY; x; innerX}
	newPos = new int*[4];

	for (int i = 0; i < NB_CELLS; i++)
	{
		newPos[i] = new int[4];
		int oldX = (*this)[i]->getInnerX();
		newPos[i][3] = (*this)[i]->getInnerY();
		newPos[i][1] = 1 - (oldX - (maxExtent - 2));
		newPos[i][0] = newPos[i][1] + navY;
		newPos[i][2] = newPos[i][3] + navX;
	}
	return newPos;
}

void Tetriminos::rotate(int** rotation)
{
	for (int i = 0; i < NB_CELLS; i++)
	{
		(*this)[i]->setY(rotation[i][0]);
		(*this)[i]->setInnerY(rotation[i][1]);
		(*this)[i]->setX(rotation[i][2]);
		(*this)[i]->setInnerX(rotation[i][3]);
	}
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
	movNavPoint(y, 0);

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
	movNavPoint(0, x);

	return this;
}
