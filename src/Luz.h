#ifndef __LUZ_H__
#define __LUZ_H__

#include "Vector.h"

class Luz {
public:
	Vector posicion;
	float intensidad;

	// Constructor
	Luz(Vector posicion_, float intensidad_) : posicion(posicion_), intensidad(intensidad_) {}
};

#endif