/**
	@author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#ifndef __IMAGEN_H__
#define __IMAGEN_H__

#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>

#include "Color.h"

using namespace std;


class Imagen {
public:

	// Constructor y destructor
	Imagen(int width, int height);
	~Imagen();
	
	// Funciones 
	void saveBMP(const char *fichero);
	void readBMP(const char *fichero);
	void savePPM(const char *fichero, string tiempo = "");
	void readPPM(const char *fichero);
	void pintar(int x, int y, Color color);    
	int getWidth();
    int getHeight();
    Color *getImagen();

private:
	
	int _width;
	int _height;
	Color *_imagen;

	};

#endif