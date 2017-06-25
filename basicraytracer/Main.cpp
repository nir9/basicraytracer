#include <stdio.h>
#include "Math.h"
#include "ImageData.h"

using namespace std;

void main() {
	vector3f v1(3, 0, 6);
	vector3f v2(2, 1, 5);

	vector3f product = CrossProduct(v1, v2);

	product.Print();


	ImageData image(1922, 1080);
	
	image.SaveToFile("C:/Users/User/Desktop/bit.bmp");

	getchar();
	
}