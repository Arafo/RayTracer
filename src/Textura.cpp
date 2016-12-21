/**
	@author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#include "Textura.h"

int Textura::getWidth() {
	return _imagen->getWidth(); 
}

int Textura::getHeight() {
	return _imagen->getHeight();
}

Color *Textura::getImagen() {
	return _imagen->getImagen();
}