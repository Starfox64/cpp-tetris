#include "stdafx.h"
#include "Utilities.h"

namespace utils
{

	std::ostream& printGameBoard(std::ostream& stream, Cell* const board[Game::HEIGHT][Game::WIDTH])
	{
		stream << " ";
		for (int i = 0; i < Game::WIDTH+1; i++) stream << "_-";
		stream << std::endl;
		for (int i = 0; i < Game::HEIGHT; i++)
		{
			stream << "||";
			for (int j = 0; j < Game::WIDTH; j++)
			{
				stream << board[i][j];
			}
			stream << "||" << std::endl;
		}
		stream << " ";
		for (int i = 0; i < Game::WIDTH+1; i++) stream << "_-";

		return stream;
	}
};

