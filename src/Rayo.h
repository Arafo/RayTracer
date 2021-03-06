/**
	@author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#ifndef __RAYO_H__
#define __RAYO_H__

#include <stdlib.h>
#include "Vector.h"

class Rayo {
public:
	Vector origen;
	Vector direccion;
	int reflexiones;
	float iRefracOrigen;
	int rebotes;

	// Constructores
	Rayo() : origen(Vector()), direccion(Vector()), reflexiones(-1), iRefracOrigen(1.0) {}

	Rayo(Vector origen_, Vector direccion_, int reflexiones_) : origen(origen_), direccion(direccion_), reflexiones(reflexiones_) {
		direccion = direccion_.normalizar();
		origen += (direccion / 1);
	}

	Rayo(Vector origen_, Vector direccion_, int reflexiones_, float iRefracOrigen_, int rebotes_) : 
	origen(origen_), direccion(direccion_), reflexiones(reflexiones_), iRefracOrigen(iRefracOrigen_), rebotes(rebotes_) {
		direccion = direccion_.normalizar();
		origen += (direccion / 1);
	}
};

#endif