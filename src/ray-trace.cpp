#include<iostream>
#include "Vector.h"

using namespace std;

int main()
{
	Vector v1(1);
	Vector v2(1.5, 2.5, 3.5);

	cout << "Productor escalar: " << v1.escalar(v2) << endl;
	Vector v3 = v1.vectorial(v2);  
	cout << "Productor vectorial: (" << v3.x << ", " << v3.y << ", " << v3.z << ") "<< endl;
	v3 = v1 + v2;
	cout << "Suma de vectores: (" << v3.x << ", " << v3.y << ", " << v3.z << ") "<< endl;
	v3 = v1 - v2;
	cout << "Resta de vectores: (" << v3.x << ", " << v3.y << ", " << v3.z << ") "<< endl;
	v3 = v1 * v2;
	cout << "Multiplicación de vectores: (" << v3.x << ", " << v3.y << ", " << v3.z << ") "<< endl;
	v3 = v1 / v2;
	cout << "División de vectores: (" << v3.x << ", " << v3.y << ", " << v3.z << ") "<< endl;

	return 0;
}