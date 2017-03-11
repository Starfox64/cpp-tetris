#include "stdafx.h"
#include "Game.h"

#ifdef _WIN32
#include <windows.h>
#define FOREGROUND_CYAN 0x0003
#define FOREGROUND_WHITE 0x0007
#else
#define ANSI_CLS		   "\033[2J"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#endif


//	CONSTRUCTORS
Game::Game()
{
	this->resetBoard();
}


Game::~Game()
{
}


//	PRIVATE METHODS
void Game::resetBoard()
{
	for (int i = 0; i < this->HEIGHT; i++)
	{
		for (int j = 0; j < this->WIDTH; j++)
		{
			this->board[i][j] = NULL;
		}
	}
}

//	PUBLIC METHODS
void Game::start()
{
	std::cout << this;
}

//	OPERATOR OVERLOADS
std::ostream& operator<<(std::ostream& stream, const Game* game)
{
	
}