#pragma once

class ImageData
{
public:
	ImageData(int width, int height);
	~ImageData();

	COLOR24 GetPixel(int x, int y);
	void SetPixel(int x, int y, COLOR24 color);

	int GetWidth();
	int GetHeight();

private:
	unsigned char* bytes;
};

struct COLOR24
{
	int r;
	int g;
	int b;
};