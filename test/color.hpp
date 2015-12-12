#pragma once
#include <ostream>

enum class color : unsigned short
{
	blue = 0x0001,
	green = 0x0002,
	red = 0x0004,

	gray = 0x0008,

	white = blue | green | red,
	normal = white,
};

inline color operator|(const color& a, const color& b)
{
	return static_cast<color>(static_cast<unsigned short>(a) | static_cast<unsigned short>(b));
}

std::ostream& operator<<(std::ostream& stream, color c);