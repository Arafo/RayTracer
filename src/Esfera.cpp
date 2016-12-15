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

float Esfera::getTipo() {
   return LUZAREA;
}

Color Esfera::getColor(Vector point) {
   if (textura == NULL)
      return color;

   // Normal entre la interseccion y la esfera
   Vector normal = (point - centro).normalizar();

   float theta = asinf(normal.y);
   float phi = atan2f(normal.x, normal.z);

   if (phi < 0)
      phi += 2 * M_PI;

   // Coordenadas U,V 
   float u = 0.5 + phi / (2 * M_PI);
   float v = 0.5 - theta / M_PI;

   int width = u * textura->getWidth();
   int height = v * textura->getHeight();        

   int pixel = width * textura->getHeight() + height;

   if (pixel > (textura->getWidth() * textura->getHeight())) {
      //cout << px << endl;
      //return Color();
   }

   Color final(textura->getImagen()[pixel % (textura->getWidth() * textura->getHeight())]);
   return final;
}