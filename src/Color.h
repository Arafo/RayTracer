#ifndef __COLOR_H__
#define __COLOR_H__

class Color {
public:
	float r, g, b, a;

	// Constructores
	Color() : r(0), g(0), b(0), a(1) {}
	Color(float r_, float g_, float b_) : r(r_), g(g_), b(b_), a(1) {}
    Color(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}

    // Funciones
    Color operator + (Color const &c) const;
    Color operator * (float c) const;
    Color operator * (Color c) const;
    Color operator / (float c) const;

};

#endif