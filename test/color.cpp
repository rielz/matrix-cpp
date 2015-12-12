#include "color.hpp"

#include <iostream>
#include <Windows.h>

std::ostream & operator<<(std::ostream & stream, color c)
{
	if (&stream == &std::cout)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(c));
	}

	return stream;
}
