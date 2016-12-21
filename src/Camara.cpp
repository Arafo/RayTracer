/**
	@author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#include "Camara.h"

void Camara::calcularUVW() {
	w = (direccion - posicion).normalizar();
	u = up.vectorial(w).normalizar();
	v = w.vectorial(u);
}