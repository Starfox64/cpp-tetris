#pragma once
class Tetriminos
{
public:
	//	STATIC ATTRIBUTES
	static const unsigned short int NB_CELLS = 4;

private:
	Cell* components[NB_CELLS];
	int maxExtent;
	int navX;
	int navY;

	void setNavPoint(int y, int x);
	void movNavPoint(int y, int x);

public:
	//	CONSTRUCTORS
	Tetriminos();
	Tetriminos(int i);
	~Tetriminos();

	//METHODS
	int top();
	int bottom();
	int left();
	int right();

	bool contains(Cell* c);

	int ** getRotation();
	void rotate(int** newPos);

	//	OPERATOR OVERLOADS
	Cell* operator[](unsigned int index);
	Tetriminos* operator+=(int y);
	Tetriminos* operator-=(int x);
};

