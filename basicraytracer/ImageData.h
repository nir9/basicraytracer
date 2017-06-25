#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

struct COLOR24
{
	int r;
	int g;
	int b;

	COLOR24(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	COLOR24() {}
};

class ImageData
{
public:
	ImageData(int width, int height);
	~ImageData();

	COLOR24 GetPixel(int x, int y);
	void SetPixel(int x, int y, COLOR24 color);

	inline int GetWidth() const;
	inline int GetHeight() const;

	HBITMAP GetHBitmap(HWND hWnd = NULL);
	void SaveToFile(std::string filePath);

private:
	unsigned char* bytes;
	int width, height;
};