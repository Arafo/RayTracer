#ifndef __ESFERA_H__
#define __ESFERA_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <Vector.h>
#include <Rayo.h>

class Esfera {
public:
	float radius;
	Vector center;

	//Constructor
	Esfera() : radius(1), center(Vector()) {}
	Esfera(int radius_, Vector center_) : radius(radius_), center(center_) {}

	//Funciones
	bool interseccion(Rayo ray);
};

#endif
