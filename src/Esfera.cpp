#include <math.h>

#include "Esfera.h"

// Devueve true si el rayo intersecta con esta esfera.
// Devuelve false en caso contrario
Interseccion Esfera::interseccion(Rayo rayo) {
   // Comprobacion geometrica. Si tF es mayor que
	// el radio al cuadrado, podemos asegurar que no
	// habra intersecciones.
	Vector L = rayo.origen - centro;
	float a = rayo.direccion.escalar(rayo.direccion);
	float b = L.escalar(rayo.direccion) * 2;
	float c = L.escalar(L) - (radio * radio);

   // Discriminante
	float d = b * b - 4 * a * c;

   if (d < 0)
      return Interseccion();

   float q = (b > 0) ? -0.5 * (b + sqrt(d)) : -0.5 * (b - sqrt(d));

   // Soluciones de la ecuacion de segundo grado
   float x0 = q / a;
   float x1 = c / q;

   if (x0 > x1)
      swap(x0, x1);

   float distancia = x0;
   // x0 negativo, se prueba con x1
   if (distancia < 0)
      distancia = x1;

   if (distancia < 0 || isnan(distancia))
      // x0 y x1 son negativos, no hay interseccion
      return Interseccion();

   // Punto de interseccion
   Vector punto = rayo.origen + (rayo.direccion * distancia);
   // Normal
   Vector normal = (punto - centro).normalizar();

   // Hay que invertir la normal si es un rayo de refraccion
   if (rayo.direccion.escalar(normal) > 0)
      normal = normal * -1;

   return Interseccion(rayo, punto, distancia, normal, this);
}