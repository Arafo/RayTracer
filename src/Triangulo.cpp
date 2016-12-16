#include <math.h>

#include "Triangulo.h"

// Devueve true si el rayo intersecta con este triangulo.
// Devuelve false en caso contrario
Interseccion Triangulo::interseccion(Rayo rayo) {
   Vector e1, e2, h, s, q, normal;
   float a, f, u, v, distance;

   e1 = Vector(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
   e2 = Vector(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

   normal = ((v1 - v0).vectorial(v2 - v0)).normalizar();

   h = rayo.direccion.vectorial(e2);
   a = e1.escalar(h);

   if (a > -0.00001 && a < 0.00001)
      return Interseccion();

   f = 1 / a;
   s = Vector(rayo.origen.x - v0.x, rayo.origen.y - v0.y, rayo.origen.z - v0.z);

   u = f * s.escalar(h);

   if (u < 0.0 || u > 1.0)
      return Interseccion();

   q = s.vectorial(e1);
   v = f * rayo.direccion.escalar(q);

   if (v < 0.0 || u + v > 1.0)
      return Interseccion();

   distance = f * e2.escalar(q);
   
   if (distance > 0.00001) {
      Vector point = rayo.origen + Vector(distance) * rayo.direccion;
      return Interseccion(rayo, point, distance, normal,  this);
   }

   return Interseccion();
}

Color Triangulo::getColor(Vector punto) {
   return color;
}