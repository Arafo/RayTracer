/**
	@author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#ifndef __LUZ_H__
#define __LUZ_H__

#define LUZ 0
#define LUZAREA 1

#include "Vector.h"

class Luz {
public:
	Vector posicion;
	float intensidad;

	// Constructor
	Luz() : posicion(Vector()), intensidad(0) {}
	Luz(Vector posicion_, float intensidad_) : posicion(posicion_), intensidad(intensidad_) {}

	// Funciones
	virtual float getTipo();

};

#endif