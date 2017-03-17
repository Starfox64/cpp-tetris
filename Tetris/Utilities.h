#pragma once

namespace utils
{

	//	METHODS
	void moveCursor(short int line, short int col);
	void changeColor(int color);
	void ShowConsoleCursor(bool showFlag);

	void initRand();

	bool isInput();
	char getInput();

	long timeStamp();

	Tetriminos* newTetriminos();
};

