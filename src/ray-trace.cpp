#include<iostream>
#include <vector>

#include "Vector.h"
#include "Imagen.h"
#include "Color.h"
#include "Rayo.h"
#include "Camara.h"
#include "Objeto.h"
#include "Esfera.h"
#include "Luz.h"

using namespace std;

std::vector<Objeto*> objetos;
std::vector<Luz*> luces;

// Funciones
void addObjeto(Objeto* objeto);
void addLuz(Luz* luz);
Color trazarRayo(const Rayo &rayo);

int main()
{

	int w = 800;
	int h = 600;

	Imagen imagen(w, h);
	Camara camara(Vector(0, 0, 100), Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), 384);

	int columnas = 0;

	// Escena
	addObjeto(new Esfera(Vector(10, 0, 0), 30));
	addObjeto(new Esfera(Vector(-7, -0.5, 90), 2));
	addObjeto(new Esfera(Vector(-40, 10, -20), 30));
	addObjeto(new Esfera(Vector(3400, 0, -10000), 2800));

	addLuz(new Luz(Vector(50, 50, 1000), 0.9));

	for (int x = 0; x < w; x++) {

		// Actualiza el porcentaje completado
		columnas++;
		float porcentaje = columnas/(float)w * 100;
		cout << '\r' << (int)porcentaje << '%';
		fflush(stdout);

		for (int y = 0; y < h; y++) {

			float rayoX = (x - w / 2) / 2.0f;
			float rayoY = (y - h / 2) / 2.0f;
			float anchuraPixel = rayoX - (x + 1 - w / 2) / 2.0f;
			float inicioX = rayoX - anchuraPixel / 2.0f;
			float inicioY = rayoY - anchuraPixel / 2.0f;
			float escala = camara.f / (float)w;

			Vector punto = camara.direccion - 
				(camara.u * (inicioX + anchuraPixel) * escala) + 
				(camara.v * (inicioY + anchuraPixel) * escala);
			Rayo rayo(camara.posicion, punto - camara.posicion);
			//cout << "Rayo: " << rayo.origen << " -> " << rayo.direccion << endl;
			Color color = trazarRayo(rayo);
			imagen.pintar(x, y, color);
		}
	}
	imagen.saveBMP("imagen.bmp");
	imagen.savePPM("imagen.ppm");

	return 0;
}

//
Color trazarRayo(const Rayo &rayo) {
	bool interseccion;
	for (vector<Objeto*>::iterator itr = objetos.begin(); itr < objetos.end(); itr++) {
		 interseccion = (*itr)->interseccion(rayo);
		 if (interseccion) 
		 	break;
	}

	if (interseccion) {
		return Color(.4, .3, .7);
	}
	return Color();
}

// Añade un objeto a la lista de objetos
void addObjeto(Objeto* objeto) {
	objetos.push_back(objeto);
}

// Añade una luz a la lista de luces
void addLuz(Luz* luz) {
	luces.push_back(luz);
}
