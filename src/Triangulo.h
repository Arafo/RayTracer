#ifndef __TRIANGULO_H__
#define __TRIANGULO_H__

#include "Vector.h"
#include "Rayo.h"
#include "Objeto.h"
#include "Interseccion.h"

class Triangulo : public Objeto {
public:
  Vector v0, v1, v2;

  // Constructores
  Triangulo(Vector v0_, Vector v1_, Vector v2_) :  Objeto(), v0(v0_), v1(v1_), v2(v2_) {}

  Triangulo(Vector v0_, Vector v1_, Vector v2_, Color color, float kd, float ks, float iEspecular, float iReflex, float iRefrac, float cRefrac) :
  Objeto(color, kd, ks, iEspecular, iReflex, iRefrac, cRefrac), v0(v0_), v1(v1_), v2(v2_) {}

  // Funciones
  virtual Interseccion interseccion(Rayo);
  virtual Color getColor(Vector);
};

#endif