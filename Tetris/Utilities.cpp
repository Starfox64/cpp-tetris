#include "stdafx.h"
#include "Utilities.h"

#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else //unix
#include <unistd.h>
#endif


namespace utils
{
	void ShowConsoleCursor(bool showFlag)//this is available on stackoverflow
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void moveCursor(short int line, short int col)
	{
		#ifdef _WIN32
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { col, line });
		#else
		std::cout << "\033[" << line << ";" << col << "H";
		#endif
	}

	void changeColor(int color)
	{
#ifdef _WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else//unix
#endif
	}

	bool isInput()
	{
#ifdef _WIN32
		return (_kbhit() != 0);
#else
		//unix
#endif
	}

	char getInput()
	{
#ifdef _WIN32
		int g = _getch();
		if (g == 'H' || g == 'h')
			return 'H';
		if (g == 0 || g == 224)
		{
			int i = _getch();
			switch (i)
			{
			case 75://left arrow
				return 'L';
			case 72://up arrow
				return 'U';
			case 77://right arrow
				return 'R';
			case 80://down arrow
				return 'D';
			default:
				return ' ';
			}
		}
#else
		//unix
#endif
	}

	long timeStamp()
	{
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

	void initRand()
	{
		srand(timeStamp());
	}

	Tetriminos* newTetriminos()
	{
		int i = rand() % 7;

		return new Tetriminos(i);
	}

};

