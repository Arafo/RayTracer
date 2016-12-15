#ifndef __ESFERA_H__
#define __ESFERA_H__

#include "Vector.h"
#include "Rayo.h"
#include "Objeto.h"
#include "Interseccion.h"
#include "Luz.h"

class Esfera : public Objeto, public Luz {
public:
	Vector centro;
	float radio;

	// Constructores
	Esfera(Vector centro_, float radio_) : Objeto(), Luz(), centro(centro_), radio(radio_) {}

	Esfera(Vector centro_, float radio_, Color color, float iEspecular, float iReflex, float iRefrac, float cRefrac) :
	Objeto(color, iEspecular, iReflex, iRefrac, cRefrac), Luz(), centro(centro_), radio(radio_) {}

	Esfera(Vector centro_, float radio_, Color color, float iEspecular, float iReflex, float iRefrac, float cRefrac, Textura& textura) :
	Objeto(color, iEspecular, iReflex, iRefrac, cRefrac, textura), Luz(), centro(centro_), radio(radio_) {}

	Esfera(Vector centro_, float radio_, float intensidad_) :
	Luz(centro_, intensidad_), centro(centro_), radio(radio_) {
	}

	// Funciones
	virtual Interseccion interseccion(Rayo);
	virtual float getTipo();
	virtual Color getColor(Vector);

};

#endif
