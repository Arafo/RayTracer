#include "Color.h"

Color Color::operator+ (Color const &c) const {
	Color o;
	o.r = c.r + r;
	o.g = c.g + g;
	o.b = c.b + b;

	return o;
}

Color Color::operator* (float cantidad) const {
	Color o;
	o.r = r * cantidad;
	o.g = g * cantidad;
	o.b = b * cantidad;

	return o;
}