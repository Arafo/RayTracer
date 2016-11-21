#ifndef __OBJETO_H__
#define __OBJETO_H__

#include "Color.h"

class Interseccion;
class Rayo;

class Objeto {
public:
	Color color;
	float iEspecular;
	float iReflexion;
	float iRefraccion;
	float cRefraccion;

	// Constructores
	Objeto() : color(Color()), iEspecular(0), iReflexion(-1), iRefraccion(-1), cRefraccion(-1) {}

	Objeto(Color color_, float iEspecular_, float iReflexion_, float iRefraccion_, float cRefraccion_) : 
	color(color_), iEspecular(iEspecular_), iReflexion(iReflexion_), iRefraccion(iRefraccion_), cRefraccion(cRefraccion_) {}

	// El igual a 0 significa que es un método virtual puro y
	// todas la clases que hereden de esta deben implementarla
	virtual Interseccion interseccion(Rayo) = 0;
};

#endif