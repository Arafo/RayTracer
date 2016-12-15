#ifndef __OBJETO_H__
#define __OBJETO_H__

#include "Color.h"
#include "Textura.h"

class Interseccion;
class Rayo;
class Vector;

class Objeto {
public:
	Color color;
	float iEspecular;
	float iReflexion;
	float iRefraccion;
	float cRefraccion;
	Textura* textura;

	// Constructores
	Objeto() : color(Color()), iEspecular(0), iReflexion(-1), iRefraccion(-1), cRefraccion(-1) {}

	Objeto(Color color_, float iEspecular_, float iReflexion_, float iRefraccion_, float cRefraccion_) : 
	color(color_), iEspecular(iEspecular_), iReflexion(iReflexion_), iRefraccion(iRefraccion_), cRefraccion(cRefraccion_) {}

	Objeto(Color color_, float iEspecular_, float iReflexion_, float iRefraccion_, float cRefraccion_, Textura& textura_) : 
	color(color_), iEspecular(iEspecular_), iReflexion(iReflexion_), iRefraccion(iRefraccion_), cRefraccion(cRefraccion_), textura(&textura_) {}

	// El igual a 0 significa que es un método virtual puro y
	// todas la clases que hereden de esta deben implementarla
	virtual Interseccion interseccion(Rayo) = 0;

	virtual Color getColor(Vector) = 0;

};

#endif