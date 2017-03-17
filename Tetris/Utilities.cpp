#include "stdafx.h"
#include "Utilities.h"

#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else //unix
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <stropts.h>
#endif


namespace utils
{
	void ShowConsoleCursor(bool showFlag)
	{
#ifdef _WIN32
		//this is available on stackoverflow
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
#else//unix
		if (showFlag)
			std::cout << "\e[?25l";
		else
			std::cout << "\e[?25h";
#endif
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
		char * unixColor;
		switch (color)
		{
		case 8://black
			unixColor = 0;
			break;
		case 12://red
			unixColor = 1;
			break;
		case 10://green
			unixColor = 2;
			break;
		case 14://yellow
			unixColor = 3;
			break;
		case 9://blue
			unixColor = 4;
			break;
		case 13://magenta
			unixColor = 5;
			break;
		case 11://cyan
			unixColor = 6;
			break;
		case 15://white
			unixColor = 7;
			break;
		}
		std::cout << "\033[" << 30 + unixColor << ";1m";
#endif
	}

	bool isInput()
	{
#ifdef _WIN32
		return (_kbhit() != 0);
#else
		//M
		static const int STDIN = 0;
		static bool initialized = false;

		if (!initialized) {
			// Use termios to turn off line buffering
			termios term;
			tcgetattr(STDIN, &term);
			term.c_lflag &= ~ICANON;
			tcsetattr(STDIN, TCSANOW, &term);
			setbuf(stdin, NULL);
			initialized = true;
		}

		int bytesWaiting;
		ioctl(STDIN, FIONREAD, &bytesWaiting);
		return bytesWaiting;
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
		//this is available on stack overflow
		char buf = 0;
		struct termios old = { 0 };
		fflush(stdout);
		if (tcgetattr(0, &old)<0)
			perror("tcsetattr()");
		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = 1;
		old.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSANOW, &old)<0)
			perror("tcsetattr ICANON");
		if (read(0, &buf, 1)<0)
			perror("read()");
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		if (tcsetattr(0, TCSADRAIN, &old)<0)
			perror("tcsetattr ~ICANON");
		return buf;
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

