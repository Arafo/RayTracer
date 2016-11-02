#include "Esfera.h"

// Devueve true si el rayo intersecta con esta esfera.
// Devuelve false en caso contrario
bool Esfera::interseccion(Rayo rayo) {
	// Comprobacion geometrica. Si tF es mayor que
	// el radio al cuadrado, podemos asegurar que no
	// habra intersecciones.
	Vector L = rayo.origen - centro;
	float a = rayo.direccion.escalar(rayo.direccion);
	float b = L.escalar(rayo.direccion) * 2;
	float c = L.escalar(L) - (radio * radio);

	float d = b * b - 4 * a * c;
	if (d <= 0) return false;
	return true;
}
