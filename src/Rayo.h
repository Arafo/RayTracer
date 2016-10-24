#ifndef __RAYO_H__
#define __RAYO_H__

#include <stdlib.h>
#include "Vector.h"

class Rayo {
public:
	Vector origen;
	Vector direccion;

	// Constructores
	Rayo() : origen(Vector()), direccion(Vector()) {}
	Rayo(Vector origen_, Vector direccion_) : origen(origen_), direccion(direccion_) {}

};

#endif