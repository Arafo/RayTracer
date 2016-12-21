/**
	@author Rafael Marcén Altarriba (650435)
    @author Jaime Puig Ortega (647286)
*/

#include "Color.h"

// Suma de colores
Color Color::operator+ (Color const &c) const {
	Color o;
	o.r = c.r + r;
	o.g = c.g + g;
	o.b = c.b + b;

	return o;
}

// Multiplicación de color por número
Color Color::operator* (float cantidad) const {
	Color o;
	o.r = r * cantidad;
	o.g = g * cantidad;
	o.b = b * cantidad;

	return o;
}

// Multiplicación de color por color
Color Color::operator* (Color color) const {
	Color o;
	o.r = r * color.r;
	o.g = g * color.g;
	o.b = b * color.b;

	return o;
}

// División de color entre número
Color Color::operator/ (float cantidad) const {
	Color o;
	o.r = r / cantidad;
	o.g = g / cantidad;
	o.b = b / cantidad;

	return o;
}