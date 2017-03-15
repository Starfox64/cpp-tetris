// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>

int main()
{
	Game* g = new Game();
	g->start();

	std::cout << std::endl;
	system("pause");
    return 0;
}

