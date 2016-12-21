/**
    @author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#ifndef __TEXTURA_H__
#define __TEXTURA_H__


#include "Imagen.h"

class Textura {
public:
    Textura() {}
    Textura(const char *fichero) {
        _imagen = new Imagen(0, 0);
        _imagen->readPPM(fichero);
    }

    ~Textura() {}

    // Funciones
	int getWidth();
    int getHeight();
    Color *getImagen();

private:
    Imagen* _imagen;
};

#endif