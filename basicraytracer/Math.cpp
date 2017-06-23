#include "Math.h"
#include <stdio.h>
#include <iostream>
using namespace std;
// operatoroverloading *
float DotProduct(vector3f v1, vector3f v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// Perhaps differently... (not returning a copy..)
vector3f CrossProduct(vector3f& v1, vector3f& v2)
{
	vector3f product(0,0,0);
	product.x = v1.y * v2.z - v2.y * v1.z;
	product.y = -(v1.x * v2.z - v2.x * v1.z);
	product.z = v1.x * v2.y - v2.x * v1.y;
	return product;
}

vector3f::vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void vector3f::Multiply(float by)
{
	x *= by;
	y *= by;
	z *= by;
}

void vector3f::Print()
{
	cout << "X: " << this->x << " Y: " << this->y << " Z: " << this->z << endl;
}
