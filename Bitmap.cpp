#include "Bitmap.h"
#include "BitmapHeaderFile.h"
#include "BitmapInfoHeader.h"
#include <string>
#include <fstream>
using namespace std;

Bitmap::Bitmap(int width, int height) : m_Pixel(new uint8_t[width * height * 3])
{
		m_width = width;
		m_height = height;
}

bool Bitmap::write(string fileName)
{
		BitmapHeaderFile  headerfile;
		BitMapInfoHeader infoFile;

		headerfile.fileSize = sizeof(headerfile) + sizeof(infoFile) + (m_width * m_height * 3);
		headerfile.dataOffset = sizeof(headerfile) + sizeof(infoFile);

		infoFile.width = m_width;
		infoFile.height = m_height;

		ofstream file;
		file.open(fileName, ios::out | ios::binary);

		if (!file)
		{
			return false;
		}
		file.write((char*)&headerfile, sizeof(headerfile));
		file.write((char*)&infoFile, sizeof(infoFile));
		file.write((char*)m_Pixel.get(), m_width * m_height * 3);
		file.close();
		return false;
}
void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
		uint8_t* pixelData = m_Pixel.get();

		pixelData += (3 * y * m_width) + (3 * x);

		pixelData[0] = blue;
		pixelData[1] = green;
		pixelData[2] = red;

}




