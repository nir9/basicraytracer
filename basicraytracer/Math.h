#pragma once
class vector3f
{
public:
	float x;
	float y;
	float z;
	vector3f(float x, float y, float z);

	void Multiply(float by);
	void Print();
};

float DotProduct(vector3f v1, vector3f v2);
vector3f CrossProduct(vector3f& v1, vector3f& v2);