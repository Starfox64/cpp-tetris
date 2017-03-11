#pragma once

class Cell
{
private:
	//	ATTRIBUTES
	int x;
	int y;
	bool falling;

public:
	//	CONSTRUCTORS
	Cell();
	Cell(int y, int x);
	Cell(int y, int x, bool falling);
	~Cell();

	//	GETTERS
	int getX();
	int getY();
	bool isFalling();

	//	SETTERS
	void setX(int x);
	void setY(int y);
	void setFalling(bool falling);

	//	OPERATOR OVERLOADS
	friend std::ostream& operator<<(std::ostream& stream, const Cell* c);
};

