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

	// Constructores
	Rayo() : origen(Vector()), direccion(Vector()), reflexiones(-1), iRefracOrigen(1.0) {}

	Rayo(Vector origen_, Vector direccion_, int reflexiones_) : origen(origen_), direccion(direccion_), reflexiones(reflexiones_) {
		direccion = direccion_.normalizar();
		origen += (direccion / 1);
	}

	Rayo(Vector origen_, Vector direccion_, int reflexiones_, float iRefracOrigen_) : 
	origen(origen_), direccion(direccion_), reflexiones(reflexiones_), iRefracOrigen(iRefracOrigen_) {
		direccion = direccion_.normalizar();
		origen += (direccion / 1);
	}



};

#endif