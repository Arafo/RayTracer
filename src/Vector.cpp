/**
   @author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#include <math.h>
#include "Vector.h"

// Producto escalar
float Vector::escalar(Vector const &v) const {
   return x * v.x + y * v.y + z * v.z;
}

// Producto vectorial
Vector Vector::vectorial(Vector const &v) const {
   return Vector(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);
}

// Normalizar
Vector Vector::normalizar() {
   return (*this) /= sqrtf(x * x + y * y + z * z);
}

float Vector::longitud() const {
   return sqrtf(x*x + y*y + z*z);
}

// Suma de vectores
Vector Vector::operator + (Vector const &v) const {
   return Vector(x + v.x, y + v.y, z + v.z);
}

// Suma de vectores
Vector & Vector::operator += (Vector const &v) {
   x += v.x;
   y += v.y;
   z += v.z;

   return * this;
}

// Resta de vectores
Vector Vector::operator - (Vector const &v) const {
   return Vector(x - v.x, y - v.y, z - v.z);
}

// Multiplicacion de vectores
Vector Vector::operator * (Vector const &v) const {
   return Vector(x * v.x, y * v.y, z * v.z);
}

// Division de vectores
Vector Vector::operator / (Vector const &v) const {
   return Vector(x / v.x, y / v.y, z / v.z);
}

// Division de vectores
Vector & Vector::operator /= (Vector const &v) {
   x /= v.x;
   y /= v.y;
   z /= v.z;

   return * this;
}

ostream & operator << (ostream &strm, const Vector &v) {
	return strm << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}