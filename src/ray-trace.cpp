#include<iostream>

#include "Vector.h"
#include "Imagen.h"

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

	int w = 800;
	int h = 600;
	int columnas = 0;

	Imagen imagen(w, h);

	for (int x = 0; x < w; x++) {

		// Actualiza el porcentaje completado
		columnas++;
		float porcentaje = columnas/(float)w * 100;
		cout << '\r' << (int)porcentaje << '%';
		fflush(stdout);

		for (int y = 0; y < h; y++) {
			Color color(x, y, x + y);
			imagen.pintar(x, y, color);
		}
	}
	imagen.saveBMP("imagen.bmp");
	imagen.savePPM("imagen.ppm");

	return 0;
}