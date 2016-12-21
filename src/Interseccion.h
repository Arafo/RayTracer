/**
  @author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#ifndef __INTERSECCION_H__
#define __INTERSECCION_H__

#include <limits>
#include "Vector.h"
#include "Objeto.h"
#include "Color.h"
#include "Rayo.h"

class Interseccion {
public:
  Rayo rayo;
  bool hayInterseccion;
  Vector interseccion;
  float distancia;
  Vector normal;
  Objeto* objeto;

  // Constructores
  Interseccion(Rayo rayo_, Vector interseccion_, float distancia_, Vector normal_, Objeto* objeto_) :
    rayo(rayo_), hayInterseccion(true), interseccion(interseccion_), distancia(distancia_), normal(normal_), objeto(objeto_) {}

  Interseccion() : rayo(Rayo()), hayInterseccion(false), interseccion(Vector()), 
    distancia(std::numeric_limits<float>::max()), normal(Vector()), objeto(NULL) {}

};

#endif