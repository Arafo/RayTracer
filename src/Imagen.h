#ifndef __IMAGEN_H__
#define __IMAGEN_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

#include "Color.h"

class Imagen {
public:

	// Constructor y destructor
	Imagen(int width, int height);
	~Imagen();
	
	// Funciones 
	void saveBMP(const char *fichero);
	void savePPM(const char *fichero);
	void pintar(int x, int y, Color color);

private:
	
	int _width;
	int _height;
	Color *_imagen;

	};

#endif