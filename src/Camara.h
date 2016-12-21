#ifndef __CAMARA_H__
#define __CAMARA_H__

#include "Vector.h"

class Camara {
public:
   Vector posicion;  // Posicion de la camara
   Vector direccion; // Direccion de la camara
   Vector up;
   Vector u, v, w;   // Sistema de la camara
   float f;          // Separacion ojo-pantalla

   // Constructores
   Camara() {
      posicion = Vector(0.0, 0.0, 100.0);
      direccion = Vector(0.0, 0.0, 0.0);
      up = Vector(0.0, 1.0, 0.0);
      f = 1000;

      calcularUVW();
   }

   Camara(Vector posicion_, Vector direccion_, Vector up_, float f_) :
   posicion(posicion_), direccion(direccion_), up(up_), f(f_) {
      calcularUVW();
   }

   // Funciones
   void calcularUVW();
};

#endif
