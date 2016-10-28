#ifndef __ESFERA_H__
#define __ESFERA_H__

#include "Vector.h"
#include "Rayo.h"
#include "Objeto.h"

class Esfera : public Objeto {
public:
	Vector centro;
	float radio;

	// Constructor
	Esfera(Vector centro_, float radio_) : centro(centro_), radio(radio_) {}

	// Funciones
	virtual bool interseccion(Rayo);
};

#endif
