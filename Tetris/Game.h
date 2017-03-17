#pragma once

class Game
{
public:
	//	STATIC ATTRIBUTES
	static const int HEIGHT = 22;
	static const int WIDTH = 10;

private:
	//	ATTRIBUTES
	Cell* board[HEIGHT][WIDTH];

	Tetriminos* currentTet;
	Tetriminos* nextTet;

	bool running;
	bool helpDrawn;
	long score;
	int level;

	//	METHODS
	void resetBoard();
	void addTetToBoard();
	void takeTetOffBoard();
	void spawnTet();
	
	bool isCellFree(int y, int x);
	bool isBottomFree();
	bool isSideFree(const char side);

	void deleteLine(int y);
	void pushBoardDown(int emptyLine);
	void deleteLines();

	void moveTet(const char direction);

	void drawBorders();
	void drawHelp();
	void drawNextTet();

public:
	//	CONSTRUCTORS
	Game();
	~Game();

	//	METHODS
	void start();

	//	OPERATOR OVERLOADS
	friend std::ostream& operator<<(std::ostream& stream, const Game* game);
};

