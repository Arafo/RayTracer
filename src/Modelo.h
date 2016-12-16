#ifndef __MODELO_H__
#define __MODELO_H__

#include <vector>

#include "Vector.h"
#include "Color.h"
#include "Objeto.h"

class Modelo {
public:

	// Constructor
	Modelo(string fichero_, int tamano_, Vector translacion_, Color color_) : 
	fichero(fichero_), tamano(tamano_), translacion(translacion_), color(color_){}
	
	// Funciones 
	void cargar(vector<Objeto*>& objetos);

private:
	
	string fichero;
	int tamano;
	Vector translacion;
	Color color;

	};

#endif