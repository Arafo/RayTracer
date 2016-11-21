#ifndef __ESFERA_H__
#define __ESFERA_H__

#include "Vector.h"
#include "Rayo.h"
#include "Objeto.h"
#include "Interseccion.h"

class Esfera : public Objeto {
public:
	Vector centro;
	float radio;

	// Constructores
	Esfera(Vector centro_, float radio_) : Objeto(), centro(centro_), radio(radio_) {}

	Esfera(Vector centro_, float radio_, Color color, float iEspecular, float iReflex, float iRefrac, float cRefrac) :
	Objeto(color, iEspecular, iReflex, iRefrac, cRefrac), centro(centro_), radio(radio_) {}

	// Funciones
	virtual Interseccion interseccion(Rayo);
};

#endif
