#ifndef _GLOBAL_DEFINES_HPP_
#define _GLOBAL_DEFINES_HPP_

typedef unsigned char _BYTE;
typedef unsigned long _DWORD;
typedef unsigned short _WORD;

#define _USE_MATH_DEFINES
#include <math.h>

struct RGBData
{
    RGBData() : red(0x00), green(0x00), blue(0x00), alpha(0xFF) { }
    RGBData(_BYTE r, _BYTE g, _BYTE b) : red(r), blue(b), green(g), alpha(0xFF) { }
    RGBData(_BYTE r, _BYTE g, _BYTE b, _BYTE a) : red(r), blue(b), green(g), alpha(a) { }
	_BYTE red;
	_BYTE green;
	_BYTE blue;
	_BYTE alpha;
};

inline double Round(double value)
{
	return floor(value + 0.5);
}

#endif