#include "ImageData.h"
#include <vector>

ImageData::ImageData(int width, int height)
{
	this->width = width;
	this->height = height;

	this->bytes = new unsigned char[width * height * 3];
	
	for (int i = 0; i < width * height * 3; i++)
		bytes[i] = 0;
}

ImageData::~ImageData()
{
	delete[] bytes;
}

COLOR24 ImageData::GetPixel(int x, int y)
{
	int r = bytes[(3  *x + 0) + (y * width)];
	int g = bytes[(3 * x + 1) + (y * width)];
	int b = bytes[(3 * x + 2) + (y * width)];

	return COLOR24(r, g, b);
}

void ImageData::SetPixel(int x, int y, COLOR24 color)
{
	bytes[(3 * x + 0) + (y * width)] = color.r;
	bytes[(3 * x + 1) + (y * width)] = color.g;
	bytes[(3 * x + 2) + (y * width)] = color.b;
}

inline int ImageData::GetWidth() const
{
	return width;
}

inline int ImageData::GetHeight() const
{
	return height;
}

HBITMAP ImageData::GetHBitmap(HWND hWnd = NULL)
{
	BITMAPINFOHEADER bih;

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = -height; // Height is negative for top-to-bottom writing on y-axis
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 10;
	bih.biYPelsPerMeter = 10;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	BITMAPINFO* bmi = (BITMAPINFO*)&bih;

	std::vector<unsigned char> data;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) /*Column loop forwards*/
		{
			/*compute pixel values*/
			unsigned char r = bytes[(3 * x + 0) + (y * width)];
			unsigned char g = bytes[(3 * x + 1) + (y * width)];
			unsigned char b = bytes[(3 * x + 2) + (y * width)];

			data.push_back(b);
			data.push_back(g);
			data.push_back(r);
			/*fwrite(&b, 1, 1, file);
			fwrite(&g, 1, 1, file);
			fwrite(&r, 1, 1, file);*/
		}

		// Padding on x-axis so that the byte-count divides by 4
		if ((width * 3) % 4 != 0)
		{
			unsigned char pad = 0;
			unsigned short padCount = 4 - ((width * 3) % 4);

			for (unsigned short i = 0; i < padCount; i++)
				//fwrite(&pad, 1, 1, file);
				data.push_back(pad);
		}
	}

	HDC hdc = GetDC(hWnd);
	HBITMAP result = CreateDIBitmap(hdc, &bih, CBM_INIT, data.data(), bmi, DIB_RGB_COLORS);
	
	ReleaseDC(hWnd, hdc);

	return result;
}

void ImageData::SaveToFile(std::string filePath)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	unsigned short bfType = 0x4d42;
	bfh.bfType = bfType;
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize =  sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width * height * 3;
	bfh.bfOffBits = 0x36;

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = -height; // Height is negative for top-to-bottom writing on y-axis
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 10;
	bih.biYPelsPerMeter = 10;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	FILE *file = fopen(filePath.c_str(), "wb");
	if (!file)
	{
		printf("Could not write file\n");
		return;
	}

	/*Write headers*/
	fwrite(&bfh, 1, sizeof(bfh), file);
	fwrite(&bih, 1, sizeof(bih), file);

	/*Write bitmap*/
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) /*Column loop forwards*/
		{
			/*compute pixel values*/
			unsigned char r = bytes[(3*x + 0) + (y * width)];
			unsigned char g = bytes[(3*x + 1) + (y * width)];
			unsigned char b = bytes[(3*x + 2) + (y * width)];

			fwrite(&b, 1, 1, file);
			fwrite(&g, 1, 1, file);
			fwrite(&r, 1, 1, file);
		}

		// Padding on x-axis so that the byte-count divides by 4
		if ((width * 3) % 4 != 0)
		{
			unsigned char pad = 0;
			unsigned short padCount = 4 - ((width * 3) % 4);

			for (unsigned short i = 0; i < padCount; i++)
				fwrite(&pad, 1, 1, file);
		}
	}

	fclose(file);
}