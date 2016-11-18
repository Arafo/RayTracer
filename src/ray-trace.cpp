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
#include "Interseccion.h"

using namespace std;

std::vector<Objeto*> objetos;
std::vector<Luz*> luces;

// Funciones
void addObjeto(Objeto* objeto);
void addLuz(Luz* luz);
Color trazarRayo(const Rayo &rayo);
Color calcularIluminacion(const Interseccion& interseccion);
Color calcularLuzAmbiental(const Interseccion& interseccion, const Color& color);
Color calcularLuzDifusaEspecular(const Interseccion& interseccion, const Color& color);
Color calcularLuzEspecular(const Interseccion& intersection, Luz* light);
bool estaEnSombra(const Rayo& rayo);
Interseccion interseccionMasCercana(const Rayo& rayo);

int main() {
	int w = 800;
	int h = 600;

	Imagen imagen(w, h);
	Camara camara(Vector(0, 0, 100), Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), 384);

	int columnas = 0;

	// Escena
	addObjeto(new Esfera(Vector(10, 0, 0), 30));
	addObjeto(new Esfera(Vector(-44, 0, -20), 20));
	//addObjeto(new Esfera(Vector(-40, 4, 0), 10));
	//addObjeto(new Esfera(Vector(-40, 10, -20), 30));
	//addObjeto(new Esfera(Vector(3400, 0, -10000), 2800));
	//addObjeto(new Esfera(Vector(-7, -0.5, 90), 2));
	addObjeto(new Esfera(Vector(w/4, -1000030, 1000), 1000000));

	addLuz(new Luz(Vector(50, 50, 100), 0.9));

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
				(camara.u * inicioX * escala) + 
				(camara.v * inicioY * escala);
			Rayo rayo(camara.posicion, punto - camara.posicion);
			//cout << punto << endl;
			//cout << "Rayo: " << rayo.origen << " -> " << rayo.direccion << endl;
			Color color = trazarRayo(rayo);
			imagen.pintar(x, y, color);
		}
	}
	imagen.saveBMP("imagen.bmp");
	//imagen.savePPM("imagen.ppm");

	return 0;
}

//
Color trazarRayo(const Rayo &rayo) {
	Interseccion interseccion = interseccionMasCercana(rayo);

	if (interseccion.hayInterseccion) {
		return calcularIluminacion(interseccion);
	}
	return Color();
}

//
Color calcularIluminacion(const Interseccion &interseccion) {
	Color color = Color(.4, .3, .7); // De prueba
	Color luzAmbiental = calcularLuzAmbiental(interseccion, color);
	Color luzDifusaEspecular = calcularLuzDifusaEspecular(interseccion, color);

	return luzAmbiental + luzDifusaEspecular;
}

//
Color calcularLuzAmbiental(const Interseccion& interseccion, const Color& color) {
	return color * 0.2;
}

//
Color calcularLuzDifusaEspecular(const Interseccion &interseccion, const Color& color) {
	// Luz difusa y especular
	Color colorDifuso(0.0, 0.0, 0.0);
	Color colorEspecular(0.0, 0.0, 0.0);

	for (vector<Luz*>::iterator itr = luces.begin(); itr < luces.end(); itr++) {
		Luz* luz = *itr;

		Vector interseccionLuz = luz->posicion - interseccion.interseccion;
		interseccionLuz.normalizar();
		float producto = interseccion.normal.escalar(interseccionLuz);

		if (producto >= 0.0f) {
			// Rayo de sombra desde el punto de interseccion a la luz
			Rayo rayoSombra = Rayo(interseccion.interseccion + 0.1, interseccionLuz);

			if (estaEnSombra(rayoSombra)) {
				// Sombra
				continue;
			}
			colorDifuso = (colorDifuso + (color * producto)) * luz->intensidad;
			colorEspecular = colorEspecular + calcularLuzEspecular(interseccion, luz);
		}
	}

	return colorDifuso + colorEspecular;
}

//
Color calcularLuzEspecular(const Interseccion& interseccion, Luz* luz) {
	Color colorEspecular(0.0, 0.0, 0.0);
	float brillo = 8;

	Vector espectador = (interseccion.rayo.origen - interseccion.interseccion).normalizar();
	Vector lightOffset = (luz->posicion - interseccion.interseccion).normalizar();
	// 2N(N escalar L) - L
	Vector reflejado = interseccion.normal * 2 * (interseccion.normal.escalar(lightOffset)) - lightOffset;

	float producto = reflejado.escalar(espectador);

	if (producto > 0) {
		float intensidadEspecular = pow(producto, brillo) * luz->intensidad;

		colorEspecular.r = intensidadEspecular;
		colorEspecular.g = intensidadEspecular;
		colorEspecular.b = intensidadEspecular;
	}
	return colorEspecular;
}

//
bool estaEnSombra(const Rayo& rayo) {
	Interseccion interseccionMin = interseccionMasCercana(rayo);
	return interseccionMin.hayInterseccion;
}

//
Interseccion interseccionMasCercana(const Rayo& rayo) {
	Interseccion interseccionMin;

	for (vector<Objeto*>::iterator itr = objetos.begin(); itr < objetos.end(); itr++) {
		 Interseccion interseccion = (*itr)->interseccion(rayo);
		 if (interseccion.hayInterseccion && interseccion.distancia < interseccionMin.distancia) 
		 	interseccionMin = interseccion;
	}

	return interseccionMin;
}

// Añade un objeto a la lista de objetos
void addObjeto(Objeto* objeto) {
	objetos.push_back(objeto);
}

// Añade una luz a la lista de luces
void addLuz(Luz* luz) {
	luces.push_back(luz);
}
