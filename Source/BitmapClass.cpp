#include "BitmapClass.hpp"

struct lWrite
{
	lWrite(unsigned int value, unsigned int size) : m_value(value), m_size(size) { }

	unsigned int m_value;
	unsigned int m_size;
};

std::ofstream& operator << (std::ofstream& out, lWrite& lwrite)
{
	for (unsigned int i = 0; i < lwrite.m_size; i++, (lwrite.m_value >>= 8))
	{
		out.put((_BYTE)(lwrite.m_value & 0xFF));
	}
	return out;
}

void Bitmap::Initialize()
{
	unsigned int sizeOfHeaders = 14 + 40;
	unsigned int paddingSize   = (4 - ((width * 3) % 4)) % 4;
	unsigned int pixelDataSize = height * ((width * 3) + paddingSize);

	bitmapFile.open(fileName.c_str(), (std::ios::out | std::ios::trunc | std::ios::binary) );

	//Bitmap File Header
	bitmapFile.put('B').put('M');
	bitmapFile << lWrite(pixelDataSize + sizeOfHeaders, 4);
	bitmapFile << lWrite(0, 4);
	bitmapFile << lWrite(sizeOfHeaders, 4);

	//Bitmap Info Header
	bitmapFile << lWrite(40, 4);
	bitmapFile << lWrite(width, 4);
	bitmapFile << lWrite(height, 4);
	bitmapFile << lWrite(1, 2);
	bitmapFile << lWrite(bpp, 2);
	bitmapFile << lWrite(0, 4);
	bitmapFile << lWrite(pixelDataSize + sizeOfHeaders, 4);
	bitmapFile << lWrite(2835, 4);
	bitmapFile << lWrite(2835, 4);
	bitmapFile << lWrite(0, 4);
	bitmapFile << lWrite(0, 4);

	initialized = true;
}

bool Bitmap::Print(RGBData *rgbdata)
{
	if (initialized)
	{
        switch (bpp)
        {
        case 8:
            std::cout << "Error: Not configured for 8 bit" << std::endl;
            return false;

        case 16:
            std::cout << "Error: Not configured for 16 bit" << std::endl;
            return false;

        case 24:
            bitmapFile << rgbdata->blue
                       << rgbdata->green
                       << rgbdata->red;
            break;

        case 32:
            bitmapFile << rgbdata->blue
                       << rgbdata->green
                       << rgbdata->red
                       << rgbdata->alpha;
            break;

        default:
            std::cout << "Error: incorrect bpp" << std::endl;
            return false;
        }
        return true;
	}
	else
	{
		std::cout << "Error: Not initialized" << std::endl;
        return false;
	}
}