#include<iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "Modelo.h"
#include "Triangulo.h"

void Modelo::cargar(vector<Objeto*>& objetos) {
	string dummy;
	vector<Vector> vertices;
	Vector centerOffset;
	float numVertex, numFaces;
	float minX = 0.0, maxX = 0.0, minY = 0.0, maxY = 0.0, minZ = 0.0, maxZ = 0.0;
	float offX = 0.0, offY = 0.0, offZ = 0.0, scale = 0.0;

	ifstream in;
	in.open(fichero.c_str(), ifstream::in);

	if (in.fail()) {
		cerr << "Error al abrir el fichero: " << fichero << endl;
		exit(EXIT_FAILURE);
	}

	cout << "Modelo: " << fichero << ", ";

	while (dummy.compare("end_header") != 0) {
		if (dummy.compare("element") == 0) {
			in >> dummy;
			if (dummy.compare("vertex") == 0)
				in >> numVertex;
			else if (dummy.compare("face") == 0)
				in >> numFaces;
		}
		else
			in.ignore(65536, '\n');
		in >> dummy;
	}

	cout << "Vertices: " << numVertex << ", ";
	cout << "Caras: " << numFaces << endl;

	for (int i = 0; i < numVertex; i++) {
		Vector v;

		in >> v.x >> v.y >> v.z;

		minX = min(minX, v.x);
		minY = min(minY, v.y);
		minZ = min(minZ, v.z);

		maxX = max(maxX, v.x);
		maxY = max(maxY, v.y);
		maxZ = max(maxZ, v.z);

		vertices.push_back(v);
	}

	for (int i = 0; i < numFaces; i++) { 
		if (scale == 0.0) {
			offX = (maxX + minX) / 2;
            offY = (maxY + minY) / 2;
            offZ = (maxZ + minZ) / 2;
            centerOffset = Vector(offX, offY, offZ);

            double distance = sqrt((maxX - minX) * (maxX - minX) +
            	(maxY - minY) * (maxY - minY) +
            	(maxZ - minZ) * (maxZ - minZ));

            if (distance == 0.0)
            	exit(EXIT_FAILURE);

            scale = tamano / distance;
        }

        int face, v0, v1, v2;

        in >> face >> v0 >> v1 >> v2;

        Vector a = (vertices[v0] - centerOffset) * scale + translacion;
        Vector b = (vertices[v1] - centerOffset) * scale + translacion;
        Vector c = (vertices[v2] - centerOffset) * scale + translacion;

        // TODO: Poner los parametros del triangulo en los parametros del metodo;
        objetos.push_back(new Triangulo(a, b, c, color, -1, -1, -1, 0));
    }
    in.close();
}