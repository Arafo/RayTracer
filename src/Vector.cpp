#include "Vector.h"

// Producto escalar
float Vector::escalar(Vector const &v) const {
   return x * v.x + y * v.y + z * v.z;
}

// Producto vectorial
Vector Vector::vectorial(Vector const &v) const {
   return Vector(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);
}

// Suma de vectores
Vector Vector::operator + (Vector const &v) const {
   return Vector(x + v.x, y + v.y, z + v.z);
}

// Resta de vectores
Vector Vector::operator - (Vector const &v) const {
   return Vector(x - v.x, y - v.y, z - v.z);
}

// Multiplicación de vectores
Vector Vector::operator * (Vector const &v) const {
   return Vector(x * v.x, y * v.y, z * v.z);
}

// División de vectores
Vector Vector::operator / (Vector const &v) const {
   return Vector(x / v.x, y / v.y, z / v.z);
}