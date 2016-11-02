#ifndef __OBJETO_H__
#define __OBJETO_H__

class Interseccion;
class Rayo;

class Objeto {
public:
	// El igual a 0 significa que es un método virtual puro y
	// todas la clases que hereden de esta deben implementarla
	virtual Interseccion interseccion(Rayo) = 0;
};

#endif