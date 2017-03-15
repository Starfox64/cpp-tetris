#pragma once
class Tetriminos
{
public:
	//	STATIC ATTRIBUTES
	static const unsigned short int NB_CELLS = 4;

private:
	Cell* components[NB_CELLS];

public:
	//	CONSTRUCTORS
	Tetriminos();
	~Tetriminos();

	//METHODS
	int top();
	int bottom();
	int left();
	int right();

	bool contains(Cell* c);

	//	OPERATOR OVERLOADS
	Cell* operator[](unsigned int index);
	Tetriminos* operator+=(int y);
	Tetriminos* operator-=(int x);
};

