#include "stdafx.h"
#include "Game.h"

#ifdef _WIN32
#include <windows.h>
#define FOREGROUND_CYAN 0x0003
#define FOREGROUND_WHITE 0x0007
#else
//move to [L][C]: \033[<L>;<C>H
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
	for (int i = 0; i < Game::HEIGHT; i++)
	{
		for (int j = 0; j < Game::WIDTH; j++)
		{
			this->board[i][j] = NULL;
		}
	}
}

void Game::addTetToBoard()
{
	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
	{
		this->board[(*currentTet)[i]->getY()][(*currentTet)[i]->getX()] = (*currentTet)[i];
	}
}

void Game::spawnTet()
{
	delete currentTet;
	currentTet = nextTet;
	nextTet = new Tetriminos();
	addTetToBoard();
}

bool Game::isBottomFree()
{
	if (currentTet->bottom() + 1 >= Game::HEIGHT)
		return false;
	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
	{
		if (board[(*currentTet)[i]->getY() + 1][(*currentTet)[i]->getX()] != NULL)
			if (!currentTet->contains(board[(*currentTet)[i]->getY() + 1][(*currentTet)[i]->getX()]))
				return false;
	}
	return true;
}

bool Game::isSideFree(const char side)
{
	int k;
	if (side == 'L')
	{
		k = -1;
		if (currentTet->left() + k < 0)
			return false;
	}
	else
	{
		k = 1;
		if (currentTet->right() + k >= Game::WIDTH)
			return false;
	}

	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
	{
		if (board[(*currentTet)[i]->getY()][(*currentTet)[i]->getX() + k] != NULL)
			if (!currentTet->contains(board[(*currentTet)[i]->getY()][(*currentTet)[i]->getX() + k]))
				return false;
	}
	
	return true;
}

void Game::moveTet(const char direction)
{
	int y, x;
	switch (direction)
	{
	case 'D':
		y = 1;
		x = 0;
		break;
	case 'L':
		y = 0;
		x = -1;
		break;
	case 'R':
		y = 0;
		x = 1;
		break;
	case 'U':
		y = -1;
		x = 0;
		break;
	}
	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
	{
		board[(*currentTet)[i]->getY() + y][(*currentTet)[i]->getX() + x] = (*currentTet)[i];
		board[(*currentTet)[i]->getY()][(*currentTet)[i]->getX()] = NULL;
	}
}

//	PUBLIC METHODS
void Game::start()
{
	this->currentTet = new Tetriminos();
	this->addTetToBoard();
	this->nextTet = new Tetriminos();

	int i = 0;
	std::cout << this << i;
	utils::wait(1000);
	i++;
	while (true)
	{
		if (isBottomFree())
		{
			moveTet('D');
			(*currentTet) += 1;
		}
		else
		{
			spawnTet();
		}
			
		std::cout << this << i;
		i++;
		utils::wait(500);
	}
}

//	OPERATOR OVERLOADS
std::ostream& operator<<(std::ostream& stream, const Game* game)
{
	utils::moveCursor(0, 0);

	stream << " ";
	for (int i = 0; i < Game::WIDTH + 1; i++) stream << "_-";
	stream << std::endl;
	for (int i = 0; i < Game::HEIGHT; i++)
	{
		stream << "||";
		for (int j = 0; j < Game::WIDTH; j++)
		{
			stream << game->board[i][j];
		}
		stream << "||" << std::endl;
	}
	stream << " ";
	for (int i = 0; i < Game::WIDTH + 1; i++) stream << "_-";


	return stream;
}
