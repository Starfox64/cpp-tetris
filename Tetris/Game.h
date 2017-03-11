#pragma once

class Game
{
private:
	//	STATIC ATTRIBUTES
	static const int HEIGHT = 22;
	static const int WIDTH = 10;

	//	ATTRIBUTES
	Cell* board[HEIGHT][WIDTH];

	//	METHODS
	void resetBoard();

public:
	//	CONSTRUCTORS
	Game();
	~Game();

	//	METHODS
	void start();

	//	OPERATOR OVERLOADS
	friend std::ostream& operator<<(std::ostream& stream, const Game* game);
};

