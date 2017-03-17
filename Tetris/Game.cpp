#include "stdafx.h"
#include "Game.h"

#include <chrono>


//	CONSTRUCTORS
Game::Game()
{
	this->resetBoard();
	this->running = true;
	this->score = 0;
	this->level = 0;
	this->helpDrawn = false;
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
		this->board[(*currentTet)[i]->getY()][(*currentTet)[i]->getX()] = (*currentTet)[i];
}

void Game::takeTetOffBoard()
{
	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
		board[(*currentTet)[i]->getY()][(*currentTet)[i]->getX()] = NULL;
}

void Game::spawnTet()
{
	delete currentTet;
	currentTet = nextTet;
	nextTet = utils::newTetriminos();
	drawNextTet();
	for (int i = 0; i < Game::WIDTH; i++)
	{
		if (board[0][i] != NULL || board[1][i] != NULL)
			running = false;
	}
	addTetToBoard();
}

void Game::drawNextTet()
{
	utils::moveCursor(10, 30);
	std::cout << "Next piece :";


}

bool Game::isCellFree(int y, int x)
{
	if (!(0 <= y && y < Game::HEIGHT) || !(0 <= x && x < Game::WIDTH))
		return false;
	return (board[y][x] == NULL);
}

bool Game::isBottomFree()
{
	if (currentTet->bottom() + 1 >= Game::HEIGHT)
		return false;
	for (int i = 0; i < Tetriminos::NB_CELLS; i++)
	{
		if (!isCellFree((*currentTet)[i]->getY() + 1, (*currentTet)[i]->getX()))
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
		if (!isCellFree((*currentTet)[i]->getY(), (*currentTet)[i]->getX() + k))
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
	takeTetOffBoard();
	(*currentTet) -= x;
	(*currentTet) += y;
	addTetToBoard();
}

void Game::deleteLine(int y)
{
	for (int i = 0; i < Game::WIDTH; i++)
	{
		delete board[y][i];
		board[y][i] = NULL;
	}
}

void Game::pushBoardDown(int emptyLine)
{
	for (int i = emptyLine; i > 2; i--)
	{
		for (int j = 0; j < Game::WIDTH; j++)
		{
			board[i][j] = board[i - 1][j];
			board[i - 1][j] = NULL;
		}
	}
}

void Game::deleteLines()
{
	for (int i = Game::HEIGHT - 1; i >= 3; i--)
	{
		bool isFull = true;
		for (int j = 0; j < Game::WIDTH; j++)
		{
			if (board[i][j] == NULL)
				isFull = false;
		}
		if (isFull)
		{
			deleteLine(i);
			pushBoardDown(i);
			i += 1;
			score += 10;
		}
	}
}

void Game::drawHelp()
{
	utils::moveCursor(3, 30);
	if (helpDrawn)
	{
		std::cout << "Press 'H' to display help";
		for (int i = 0; i < 20; i++) std::cout << ' ';
		for (int i = 4; i < 8; i += 1)
		{
			utils::moveCursor(i, 30);
			for (int j = 0; j < 60; j++) std::cout << ' ';
		}
		helpDrawn = false;
	}
	else
	{
		std::cout << "Use left and right arrow to move the piece,";
		utils::moveCursor(4, 30);
		std::cout << "Use up arrow to rotate the piece anti-clockwise,";
		utils::moveCursor(5, 30);
		std::cout << "Use down arrow to speed up the fall of the piece";
		utils::moveCursor(6, 30);
		std::cout << "Each line gives 10 points. Each 100 points, you level up";
		utils::moveCursor(7, 30);
		std::cout << "Speed will lineary increase until you loose ;)";

		helpDrawn = true;
	}
}

//	PUBLIC METHODS
void Game::start()
{
	//display help hint
	utils::moveCursor(3, 30);
	std::cout << "Press 'H' to display help";
	//init tetriminos
	this->nextTet = utils::newTetriminos();
	spawnTet();
	//init some vars
	bool redraw = false;

	long start = utils::timeStamp();
	long delta = 1000;//duration between each fall steps

	std::cout << this;
	//game loop
	while (running)
	{
		if (utils::isInput())//if there was an input
		{
			char input = utils::getInput();//get it

			bool doRotation = true;//will rotate
			int** rotation;//rotation matrix
			switch (input)
			{
			case 'L'://move left
				if (isSideFree('L'))
					moveTet('L');
				break;
			case 'R'://move right
				if (isSideFree('R'))
					moveTet('R');
				break;
			case 'U'://rotate
				rotation = currentTet->getRotation();//get rotation matrix
				for (int i = 0; i < Tetriminos::NB_CELLS; i++)
				{
					if (!(0 <= rotation[i][0] && rotation[i][0] < Game::HEIGHT) || !(0 <= rotation[i][2] && rotation[i][2] < Game::WIDTH))
					{
						doRotation = false; break;
					}
					if (!isCellFree(rotation[i][0], rotation[i][2]))
					{
						if ( !currentTet->contains(board[rotation[i][0]][rotation[i][2]]) )
						{//if new cell isn't free and is not in the tetriminos
							doRotation = false;
							break;
						}
					}
				}
				if (doRotation)
				{
					takeTetOffBoard();
					currentTet->rotate(rotation);
					addTetToBoard();
				}
				break;

			case 'D'://accelerate the fall
				if (isBottomFree())
				{
					moveTet('D');
					score ++;
				}
				break;
			case 'H'://display or hide help
				drawHelp();
			}
			redraw = true;//should redraw changes
		}


		if (utils::timeStamp() - start >= delta)
		{//period between fall steps has revolved;
			start = utils::timeStamp();
			if (isBottomFree())//if nothing below
			{
				moveTet('D');
			}
			else//spawn a new tetriminos
			{
				spawnTet();
				deleteLines();//delete eventually completed lines
			}
			if (score / 100 > level)
			{//level up about the score
				level++;
				if (delta > 100)
					delta -= 50;
			}
			redraw = true;//should redraw changes
			score++;
		}

		if (redraw)
		{//if changes
			std::cout << this;
			redraw = false;
		}
	}
}

//	OPERATOR OVERLOADS
std::ostream& operator<<(std::ostream& stream, const Game* game)
{
	utils::moveCursor(0, 30);
	stream << "Level : " << game->level;
	utils::moveCursor(1, 30);
	stream << "Score : " << game->score;


	utils::moveCursor(0, 0);

	stream << (char)201;
	for (int i = 0; i < Game::WIDTH * 2; i++) stream << (char)205;
	stream << (char)187 << std::endl;
	for (int i = 0; i < Game::HEIGHT; i++)
	{
		stream << (char) 186;
		for (int j = 0; j < Game::WIDTH; j++)
		{
			stream << game->board[i][j];
		}
		stream <<(char) 186 << std::endl;
	}
	stream << (char)200;
	for (int i = 0; i < Game::WIDTH * 2; i++) stream << (char) 205;
	stream << (char)188 << std::endl;

	return stream;
}
