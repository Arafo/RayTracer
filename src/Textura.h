#ifndef __TEXTURA_H__
#define __TEXTURA_H__


#include "Imagen.h"

class Textura {
public:
    Textura(const char *fichero) : _imagen(0, 0) {
        _imagen.readPPM(fichero);
    }

    ~Textura() {}

    // Funciones
	int getWidth();
    int getHeight();
    Color *getImagen();

private:
    Imagen _imagen;
};

#endif