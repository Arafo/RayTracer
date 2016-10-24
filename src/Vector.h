#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector {
public:

	float x, y, z;

	// Constructores
	Vector() : x(0.f), y(0.f), z(0.f) {}
	Vector(float valor) : x(valor), y(valor), z(valor) {}
	Vector(float valor_x, float valor_y, float valor_z) : x(valor_x), y(valor_y), z(valor_z) {}

	// Funciones
	float escalar(Vector const &v) const;
	Vector vectorial(Vector const &v) const;
	Vector normalizar();
	Vector operator + (Vector const &v) const;
	Vector operator - (Vector const &v) const;
	Vector operator * (Vector const &v) const;
	Vector operator / (Vector const &v) const;
	Vector & operator /= (Vector const &v);
};

#endif