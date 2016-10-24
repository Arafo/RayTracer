#include "Camara.h"

void Camara::calcularUVW() {
	w = (direccion - posicion).normalizar();
	u = up.vectorial(w).normalizar();
	v = w.vectorial(u);
}