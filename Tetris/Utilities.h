#pragma once

namespace utils
{

	//	METHODS
	void moveCursor(short int line, short int col);
	void wait(int ms);

	bool isInput();
	char getInput();

	long timeStamp();
};

