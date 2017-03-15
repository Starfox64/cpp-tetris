// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>

int main()
{

	Game* g = new Game();
	g->start();

	while (true)
	{
		char tbl[1] = {};
		
		if (_kbhit())
			std::cout << (char) _getch();
		
	}


	std::cout << std::endl;
	system("pause");
    return 0;
}

