#include "Esfera.h"

// Devueve true si el rayo intersecta con esta esfera.
// Devuelve false en caso contrario
bool Esfera::interseccion(Rayo rayo) {
	//Comprobacion geometrica. Si tF es mayor que
	//el radio al cuadrado, podemos asegurar que no
	//habra intersecciones.
	Vector L = centro - rayo.origen;
	float tD = L.escalar(rayo.direccion);
	float tF = L.escalar(L) - tD*tD;
	if (tF > (radio + radio)) return false;
	return true;
}
