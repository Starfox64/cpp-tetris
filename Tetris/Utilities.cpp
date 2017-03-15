#include "stdafx.h"
#include "Utilities.h"
#include <stdio.h>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else //unix
#include <unistd.h>
#endif


namespace utils
{
	void moveCursor(short int line, short int col)
	{
		#ifdef _WIN32
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { line, col });
		#else
		std::cout << "\033[" << line << ";" << col << "H";
		#endif
	}

	void wait(int ms)
	{
#ifdef _WIN32
		Sleep(ms);
#else
		if (ms < 1000)
			usleep(ms * 1000);
		else
		{
			for (int i = 0; i < ms / 500 i++)
				usleep(500);
			usleep(ms % 500);
		}
#endif	
	}

};

