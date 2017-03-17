#pragma once

class Cell
{
private:
	//	ATTRIBUTES
	int x;
	int y;

	int innerX;
	int innerY;

	int color;

public:
	//	CONSTRUCTORS
	Cell();
	Cell(int y, int x);
	Cell(int y, int innerY, int x, int innerX, int color);
	~Cell();

	//	GETTERS
	int getX();
	int getY();

	int getInnerX();
	int getInnerY();

	int getColor();

	//	SETTERS
	void setX(int x);
	void setY(int y);

	void setInnerX(int x);
	void setInnerY(int y);

	void setColor(int color);

	//	OPERATOR OVERLOADS
	friend std::ostream& operator<<(std::ostream& stream, const Cell* c);
};

