#ifndef _BITMAP_CLASS_HPP_
#define _BITMAP_CLASS_HPP_

#include "GlobalDefines.hpp"

#include <fstream>
#include <iostream>
#include <string>

class Bitmap
{
public:
	Bitmap(
        std::string  _fileName,
		unsigned int _width, 
		unsigned int _height, 
		unsigned int _bpp 
        ) : width       (_width),
            height      (_height),
            bpp         (_bpp),
            initialized (false),
            fileName    (_fileName) { }

	~Bitmap()
	{
		if (bitmapFile.is_open())
		{
			std::cout << "Closing " << fileName << std::endl;
			bitmapFile.close();
		}
	}

	void Initialize();

    bool Print(RGBData* rgbdata);

private:
	bool initialized;

	std::ofstream bitmapFile;

	_DWORD width;
	_DWORD height;
	_WORD  bpp;

	std::string fileName;
};

#endif