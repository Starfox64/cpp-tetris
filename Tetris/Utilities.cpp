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
	void moveCursor(short int line, short int col)
	{
		#ifdef _WIN32
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { col, line });
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

};

