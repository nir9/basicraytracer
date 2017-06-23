#include <stdio.h>
#include "Math.h"
using namespace std;

void main() {
	vector3f v1(3, 0, 6);
	vector3f v2(2, 1, 5);

	vector3f product = CrossProduct(v1, v2);

	product.Print();
	
	

	while(1) {}
	
}