// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	utils::ShowConsoleCursor(false);
	utils::changeColor(15);

	Game* g = new Game();
	g->start();

	std::cout << std::endl;
	system("pause");
    return 0;
}

