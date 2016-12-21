#include<iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include "Vector.h"
#include "Imagen.h"
#include "Color.h"
#include "Rayo.h"
#include "Camara.h"
#include "Objeto.h"
#include "Esfera.h"
#include "Luz.h"
#include "Modelo.h"
#include "Interseccion.h"
#include "Textura.h"

using namespace std;

// Variables globales
bool LUZ_INDIRECTA = false;
int LUZ_INDIRECTA_SAMPLES = 8;
int MAX_REBOTES = 1;
int ANTIALIASING = 1;
int w = 512;
int h = 512;
string FICHERO_BMP = "../resultados/imagen.bmp";
string FICHERO_PPM = "../resultados/imagen.ppm";
Camara camara;
Textura tex[100];
int contadorTexturas = 0;
float ka = 0.2;

std::vector<Objeto*> objetos;
std::vector<Luz*> luces;

// Funciones
void addObjeto(Objeto* objeto);
void addLuz(Luz* luz);
void leerEscena(istream& in);
Color trazarRayo(const Rayo &rayo);
Color calcularIluminacion(const Interseccion& interseccion);
Color calcularLuzAmbiental(const Interseccion& interseccion, const Color& color);
Color calcularLuzDifusaEspecular(const Interseccion& interseccion, const Color& color);
Color calcularLuzEspecular(const Interseccion& interseccion, Luz* luz);
Color calcularLuzReflexionRefraccion(const Interseccion& interseccion);
Color calcularLuzIndirecta(const Interseccion& interseccion, const Color& color);
Vector muestreoSemiesfera(const Vector &n, const float &r1, const float &r2);
Vector reflexion(const Vector& normal, const Vector& direccion);
Vector refraccion(const Vector& normal, const Vector& direccion, float n);
float reflectancia(const Vector& normal, const Vector& direccion, float n1, float n2);
bool estaEnSombra(const Rayo& rayo, float distanciaLuz);
Interseccion interseccionMasCercana(const Rayo& rayo);

int main(int argc, char** argv) {

	clock_t t1, t2;
	t1 = clock();

	// Lectura de la escena
	char* inFile = argv[1];
	if (inFile != NULL) {
		LUZ_INDIRECTA_SAMPLES = atoi(argv[2]);
		LUZ_INDIRECTA = LUZ_INDIRECTA_SAMPLES > 1 ? true : false;
		ANTIALIASING = atoi(argv[3]);

		// Nombre de la imagen
		if (argc > 4) {
			FICHERO_BMP = argv[4];
			FICHERO_PPM = argv[4];
		}
	}

	ifstream inFileStream;
	inFileStream.open(inFile, ifstream::in);

	if (inFileStream.fail()) {
		cerr << "Error al abrir el fichero:" << inFile << endl;
		//exit(EXIT_FAILURE);

		// Si no hay fichero de entrada, se utiliza la cornel box
		cout << endl << "Cornel Box" << endl;
		// Cornel Box
		w = 800, h = 600;
		LUZ_INDIRECTA = true;
		LUZ_INDIRECTA_SAMPLES = 512;
		ANTIALIASING = 2;
		camara = Camara(Vector(0, 20, 100), Vector(0.0, 14, 0.0), Vector(0.0, 1.0, 0.0), 60);
		addObjeto(new Esfera(Vector(16, -22, -300), 16, Color(0, 0, 0), 1, 1, -1, -1, 1.6, 0));
		addObjeto(new Esfera(Vector(-26, -26, -380), 12, Color(0.7, 0.7, 0), 1, 1, -1, 1, -1, 0));

		//addObjeto(new Esfera(Vector(w/4, -100030, 1000), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));	// Suelo
		//addObjeto(new Esfera(Vector(-100038, 0, 1000), 100000, Color(1, 0.32, 0.32), -1, -1, 0, 0));	// Pared Izquierda
		//addObjeto(new Esfera(Vector(100038, 0, 1000), 100000, Color(0.55, 0.76, 0.29), -1, -1, 0, 0));	// Pared Derecha
		//addObjeto(new Esfera(Vector(w/4, 0, -100440), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));		// Pared Fondo
		//addObjeto(new Esfera(Vector(w/4, 100030, 1000), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));	// Techo

		addLuz(new Luz(Vector(0, 20, -350), 0.9));

		Modelo modelo("../modelos/face.ply", 400, Vector(0, 0, -440), Color(0.9, 0.9, 0.9));
		modelo.cargar(objetos);
		Modelo modelo2("../modelos/face_top.ply", 400, Vector(0, 38, -350), Color(0.9, 0.9, 0.9));
		modelo2.cargar(objetos);
		Modelo modelo3("../modelos/face_bottom.ply", 400, Vector(0, -38, -350), Color(0.9, 0.9, 0.9));
		modelo3.cargar(objetos);
		Modelo modelo4("../modelos/face_left.ply", 400, Vector(-46, 0, -350), Color(1, 0.32, 0.32));
		modelo4.cargar(objetos);
		Modelo modelo5("../modelos/face_rigth.ply", 400, Vector(46, 0, -350), Color(0.55, 0.76, 0.29));
		modelo5.cargar(objetos);
	}

	leerEscena(inFileStream);
	inFileStream.close();

	Imagen imagen(w, h);
	int columnas = 0;

	//addLuz(new LuzArea(Vector(0, 20, -350), 0.9, Vector(0, 0, 1), Vector(1, 0, 0), 3));
	//addLuz(new Esfera(Vector(0, 20, -350), 10, 0.9));
	
	//addObjeto(new Caja(Vector(-51, -40, -200), Vector(-50, 40, -500), Color(1, 0.32, 0.32), -1, -1, -1, 0));
	//addObjeto(new Caja(Vector(-40, -40, -400), Vector(50, 40, -401), Color(0.9, 0.9, 0.9), -1, -1, -1, 0));

	//addObjeto(new Plano(Vector(0, 0, -1), 1, Color(0.9, 0, 0.9), -1, -1, -1, 0));


	#pragma omp parallel for
	for (int x = 0; x < w; x++) {

		// Actualiza el porcentaje completado
		columnas++;
		float porcentaje = columnas/(float)w * 100;
		cout << '\r' << (int)porcentaje << '%';
		fflush(stdout);

		for (int y = 0; y < h; y++) {

			float rayoX = (x - w / 2) / 2.0f;
			float rayoY = (y - h / 2) / 2.0f;
			float anchuraPixel = rayoX - (x + 1 - w / 2) / 2.0f;
			float anchuraSample = anchuraPixel / ANTIALIASING;
			float inicioX = rayoX - anchuraPixel / 2.0f;
			float inicioY = rayoY - anchuraPixel / 2.0f;
			float escala = camara.f / (float)w;
			float sample = 1.0 / (ANTIALIASING * ANTIALIASING);

			Color color(0.0, 0.0, 0.0);
			for (int xaa = 0; xaa < ANTIALIASING; xaa++) {
				for (int yaa = 0; yaa < ANTIALIASING; yaa++) {
					Vector punto = camara.direccion - 
						(camara.u * (inicioX + (xaa * anchuraSample)) * escala) + 
						(camara.v * (inicioY + (yaa * anchuraSample)) * escala);
					Rayo rayo(camara.posicion, punto - camara.posicion, 4, 1.0, 0);
					//cout << punto << endl;
					//cout << "Rayo: " << rayo.origen << " -> " << rayo.direccion << endl;
					color = color + (trazarRayo(rayo) * sample);
				}
			}

			imagen.pintar(x, y, color);
		}
	}

	t2 = clock();
	float tiempo = ((float)t2 - (float)t1);
	int segundos = tiempo / 1000;
	int minutos = segundos / 60;
	int horas = minutos / 60;
	int milisegundos = (int)tiempo % 1000;

	ostringstream ss;
	ss << "Tiempo: " << int(horas) << "h " << int(minutos % 60) << "m " << int((int)segundos % 60) << "s " << milisegundos << "ms";
	//cout << endl << "Tiempo: " << segundos << " segundos" << endl;
	cout << endl << ss.str() << endl;

	imagen.saveBMP(FICHERO_BMP.c_str());
	imagen.savePPM(FICHERO_PPM.c_str(), ss.str());

	return 0;
}

//
Color trazarRayo(const Rayo &rayo) {
	if (rayo.rebotes > MAX_REBOTES) {
		return Color();
	}

	Interseccion interseccion = interseccionMasCercana(rayo);

	if (interseccion.hayInterseccion) {
		return calcularIluminacion(interseccion);
	}
	return Color();
}

//
Color calcularIluminacion(const Interseccion &interseccion) {
	Color color = interseccion.objeto->getColor(interseccion.interseccion);
	Color luzAmbiental = calcularLuzAmbiental(interseccion, color);
	Color luzDifusaEspecular = calcularLuzDifusaEspecular(interseccion, color);
	Color luzReflexionRefraccion = calcularLuzReflexionRefraccion(interseccion);

	Color luzDirecta = luzAmbiental + luzDifusaEspecular + luzReflexionRefraccion;
	if (!LUZ_INDIRECTA)
		return luzDirecta;

	Color luzIndirecta = calcularLuzIndirecta(interseccion, color);

	//if (luzDirecta.r == 0.f && luzDirecta.g == 0.f && luzDirecta.b == 0.f) return luzIndirecta;
	//return (luzDirecta + luzIndirecta) / 2.f;
	return luzReflexionRefraccion + ((luzAmbiental + luzDifusaEspecular) / M_PI  + luzIndirecta * 2) * color;

	//return ((luzAmbiental + luzDifusaEspecular + luzReflexionRefraccion) / M_PI + luzIndirecta * 2);
}

//
Color calcularLuzAmbiental(const Interseccion& interseccion, const Color& color) {
	return color * ka;
}

//
Color calcularLuzDifusaEspecular(const Interseccion &interseccion, const Color& color) {
	// Luz difusa y especular
	Color colorDifuso(0.0, 0.0, 0.0);
	Color colorEspecular(0.0, 0.0, 0.0);

	for (vector<Luz*>::iterator itr = luces.begin(); itr < luces.end(); itr++) {
		Luz* luz = *itr;

		if (luz->getTipo() == LUZ) {
			Vector interseccionLuz = luz->posicion - interseccion.interseccion;
			float distanciaLuz = interseccionLuz.longitud();
			interseccionLuz.normalizar();
			float producto = interseccion.normal.escalar(interseccionLuz);

			if (producto >= 0.0f) {
				// Rayo de sombra desde el punto de interseccion a la luz
				Rayo rayoSombra = Rayo(interseccion.interseccion, interseccionLuz, 1, interseccion.rayo.iRefracOrigen, interseccion.rayo.rebotes);

				if (estaEnSombra(rayoSombra, distanciaLuz)) {
					// Sombra
					continue;
				}
				colorDifuso = ((colorDifuso + (color * producto)) * luz->intensidad) * interseccion.objeto->kd;
				colorEspecular = colorEspecular + calcularLuzEspecular(interseccion, luz) * interseccion.objeto->ks;
			}
		}
		/*else if (luz->getTipo() == LUZAREA) {
			Esfera* luzArea = (Esfera*)(luz);
			int samples = 8;
			for (int i = 0; i < samples; i++) {
				//float ru = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				//float rv = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				Vector offset = random_unit_vector();
				Vector posicionLuz = luzArea->centro + offset * luzArea->radio;
                //Vector posicionLuz = luzArea->posicion + (luzArea->uvec) * luzArea->llen * ru + (luzArea->lvec) * luzArea->llen * rv;
                Vector interseccionLuz = posicionLuz - interseccion.interseccion;
                float distanciaLuz = interseccionLuz.longitud();
                interseccionLuz.normalizar();

                float producto = interseccion.normal.escalar(interseccionLuz);

                if (producto >= 0.0f) {
                // Rayo de sombra desde el punto de interseccion a la luz
                	Rayo rayoSombra = Rayo(interseccion.interseccion, interseccionLuz, 1, interseccion.rayo.iRefracOrigen, interseccion.rayo.rebotes);
                	if (estaEnSombra(rayoSombra, distanciaLuz)) {
                		// Sombra
                		continue;
                	}
                	colorDifuso = (colorDifuso + (color * producto)) * luzArea->intensidad;
                	colorEspecular = colorEspecular + calcularLuzEspecular(interseccion, luzArea);
                }
			}
			colorDifuso.r = colorDifuso.r / samples;
			colorDifuso.g = colorDifuso.g / samples;
			colorDifuso.b = colorDifuso.b / samples;

			colorEspecular.r = colorEspecular.r / samples;
			colorEspecular.g = colorEspecular.g / samples;
			colorEspecular.b = colorEspecular.b / samples;
		}*/
	}

	return colorDifuso + colorEspecular;
}

//
Color calcularLuzEspecular(const Interseccion& interseccion, Luz* luz) {
	Color colorEspecular(0.0, 0.0, 0.0);
	float brillo = interseccion.objeto->iEspecular;

	if (brillo < 0) {
		return colorEspecular;
	}

	Vector espectador = (interseccion.rayo.origen - interseccion.interseccion).normalizar();
	Vector lightOffset = (luz->posicion - interseccion.interseccion).normalizar();
	// 2N(N escalar L) - L
	Vector reflejado = interseccion.normal * 2 * (interseccion.normal.escalar(lightOffset)) - lightOffset;

	float producto = reflejado.escalar(espectador);

	if (producto > 0) {
		float intensidadEspecular = pow(producto, brillo) * luz->intensidad;

		colorEspecular.r = intensidadEspecular;
		colorEspecular.g = intensidadEspecular;
		colorEspecular.b = intensidadEspecular;
	}
	return colorEspecular;
}

//
Color calcularLuzReflexionRefraccion(const Interseccion& interseccion) {
	Color colorReflexion;
	Color colorRefraccion;

	int reflexionesRestantes = interseccion.rayo.reflexiones;
	//cout << reflexionesRestantes << endl;
	
	float indiceReflexion = interseccion.objeto->iReflexion;
	float indiceRefraccionOrigen = interseccion.rayo.iRefracOrigen;
	float indiceRefraccionDestino = interseccion.objeto->iRefraccion;

	float cantidadReflexion = indiceReflexion;
	float cantidadRefraccion = 0;

	if (reflexionesRestantes <= 0 || (indiceReflexion <= 0 && indiceRefraccionDestino <= 0)) {
		return Color();
	}

	if (indiceRefraccionDestino > 0) {
		//cantidadReflexion = reflectancia(interseccion.normal, interseccion.rayo.direccion, indiceRefraccionOrigen, indiceRefraccionDestino);
		cantidadRefraccion = 1 - reflectancia(interseccion.normal, interseccion.rayo.direccion, indiceRefraccionOrigen, indiceRefraccionDestino);;
	}

	if (cantidadReflexion <= 0 && cantidadRefraccion <= 0) {
		return Color();
	}

	if (cantidadReflexion > 0) {
		Vector reflejado = reflexion(interseccion.normal, interseccion.rayo.direccion);
		Rayo rayoReflejado = Rayo(interseccion.interseccion, reflejado, reflexionesRestantes - 1, indiceRefraccionDestino, interseccion.rayo.rebotes);
		colorReflexion = trazarRayo(rayoReflejado) * cantidadReflexion;
	}

	if (cantidadRefraccion > 0) {
		Vector refractado = refraccion(interseccion.normal, interseccion.rayo.direccion, indiceRefraccionOrigen / indiceRefraccionDestino);
		Rayo rayoRefractado = Rayo(interseccion.interseccion, refractado, 1, indiceRefraccionDestino, interseccion.rayo.rebotes);
		colorRefraccion = trazarRayo(rayoRefractado) * cantidadRefraccion;
	}
     
	return colorReflexion + colorRefraccion;
}

//
Color calcularLuzIndirecta(const Interseccion& interseccion, const Color& color) {
	if (interseccion.rayo.rebotes > MAX_REBOTES) {
		//return Color();
	}

	Color colorLuzIndirecta;
	Vector Nt, Nb;
	Vector normal = interseccion.normal;
	float pdf = 1 / (2 * M_PI); 

	for (int i = 0; i < LUZ_INDIRECTA_SAMPLES; i++) {
		float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//cout << r1 << ", " << r2 << endl;

		if (fabs(normal.x) > fabs(normal.y))
			Nt = Vector(normal.z, 0, -normal.x) / sqrtf(normal.x * normal.x + normal.z * normal.z);
		else
			Nt = Vector(0, -normal.z, normal.y) / sqrtf(normal.y * normal.y + normal.z * normal.z);
		Nb = normal.vectorial(Nt);

		Vector sample = muestreoSemiesfera(normal, r1, r2);
		Vector sampleWorld(
			sample.x * Nb.x + sample.y * normal.x + sample.z * Nt.x,
			sample.x * Nb.y + sample.y * normal.y + sample.z * Nt.y,
			sample.x * Nb.z + sample.y * normal.z + sample.z * Nt.z); 
		Rayo rayoSample = Rayo(interseccion.interseccion + sampleWorld * 0.0001, sampleWorld, 1, interseccion.rayo.iRefracOrigen, interseccion.rayo.rebotes + 1);
		colorLuzIndirecta = colorLuzIndirecta + trazarRayo(rayoSample) * r1 / pdf;
	}

	//cout << colorLuzIndirecta.r << " " << colorLuzIndirecta.g << " " << colorLuzIndirecta.b << endl;
	colorLuzIndirecta.r = colorLuzIndirecta.r / LUZ_INDIRECTA_SAMPLES;
	colorLuzIndirecta.g = colorLuzIndirecta.g / LUZ_INDIRECTA_SAMPLES;
	colorLuzIndirecta.b = colorLuzIndirecta.b / LUZ_INDIRECTA_SAMPLES;

	return colorLuzIndirecta;
}

Vector muestreoSemiesfera(const Vector &n, const float &r1, const float &r2) {
    float x, y, z;

    float phi = 2.0 * M_PI * r2;
    //float cosTheta = sqrt(1.0 - r1);
    float sinTheta = sqrtf(1.0 - r1 * r1);

    x = cosf(phi) * sinTheta;
    y = r1;
    z = sinf(phi) * sinTheta;

    Vector direccion = Vector(x, y, z);
    return direccion.normalizar();
} 

// Vector reflectado
Vector reflexion(const Vector& normal, const Vector& direccion) {
	float cosI	 = -(normal.escalar(direccion));
	return direccion + normal * 2 * cosI;
}

// Vector refractado
Vector refraccion(const Vector& normal, const Vector& direccion, float n) {
	float cosI = -normal.escalar(direccion);
	float sinT2 = n * n * (1.0 - cosI * cosI);

	if (sinT2 > 1.0) {
		exit(EXIT_FAILURE);
	}

	float cosT = sqrt(1.0 - sinT2);
	return direccion * n + normal * (n * cosI - cosT);
}

// Funcion de reflectancia
float reflectancia(const Vector& normal, const Vector& direccion, float n1, float n2) {
	float n = n1 / n2;
	float cosI = -normal.escalar(direccion);
	float sinT2 = n * n * (1.0 - cosI * cosI);

	if (sinT2 > 1.0) {
	// Total Internal Reflection.
		return 1.0;
	}

	float cosT = sqrt(1.0 - sinT2);
	float r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	float rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
	return (r0rth * r0rth + rPar * rPar) / 2.0;
}

// Devuelve true si el rayo apunta a una sombra
bool estaEnSombra(const Rayo& rayo, float distanciaLuz) {
	Interseccion interseccionMin = interseccionMasCercana(rayo);
	return interseccionMin.hayInterseccion && interseccionMin.distancia < distanciaLuz;
}

//
Interseccion interseccionMasCercana(const Rayo& rayo) {
	Interseccion interseccionMin;

	for (vector<Objeto*>::iterator itr = objetos.begin(); itr < objetos.end(); itr++) {
		 Interseccion interseccion = (*itr)->interseccion(rayo);
		 if (interseccion.hayInterseccion && interseccion.distancia < interseccionMin.distancia) 
		 	interseccionMin = interseccion;
	}

	return interseccionMin;
}

// 
void leerEscena(istream& in) {
	string tipo;
	in >> tipo;
	
	while (in.good()) {
		if (tipo[0] == '#') {
			// Ignorar comentarios
			getline(in, tipo);
		}
		else if (tipo.compare("resolucion") == 0) {
			int anchura, altura;

			in >> anchura;
			in >> altura;

			w = anchura;
			h = altura;
		}
		else if (tipo.compare("camara") == 0) {
			Vector posicion, direccion, up;
			float fov;

			in >> posicion.x >> posicion.y >> posicion.z;
			in >> direccion.x >> direccion.y >> direccion.z;
			in >> up.x >> up.y >> up.z;
			in >> fov;

			camara = Camara(posicion, direccion, up, fov);
		}
		else if (tipo.compare("esfera") == 0) {
			Vector centro;
			float radio;
			Color color;
			float kd, ks, especular, reflexion, irefraccion, crefraccion;
			string textura;

			in >> centro.x >> centro.y >> centro.z;
			in >> radio;
			in >> color.r >> color.g >> color.b;
			in >> kd;
			in >> ks;
			in >> especular;
			in >> reflexion;
			in >> irefraccion;
			in >> crefraccion;
			in >> textura;

			if (textura.compare("NULL") == 0)
				addObjeto(new Esfera(centro, radio, color, kd, ks, especular, reflexion, irefraccion, crefraccion));
			else {
				//static Textura tex(&textura[0u]);
				tex[contadorTexturas] = Textura(&textura[0u]);
				addObjeto(new Esfera(centro, radio, color, kd, ks, especular, reflexion, irefraccion, crefraccion, tex[contadorTexturas]));
				contadorTexturas++;
			}

			cout << "Esfera: Centro " << centro << ", Radio " << radio << endl; 
		}
		else if (tipo.compare("luz") == 0) {
			Vector posicion;
			float intensidad;

			in >> posicion.x >> posicion.y >> posicion.z;
			in >> intensidad;

			addLuz(new Luz(posicion, intensidad));
			cout << "Luz: Posicion " << posicion << ", Intensidad " << intensidad << endl; 
		} 
		else if (tipo.compare("modelo") == 0) {
			string fichero;
			int tamano;
			Vector translacion;
			Color color;

			in >> fichero;
			in >> tamano;
			in >> translacion.x >> translacion.y >> translacion.z;
			in >> color.r >> color.g >> color.b;

			Modelo modelo(fichero, tamano, translacion, color);
			modelo.cargar(objetos);
		}
		else {
			cerr << "Tipo no encontrado: " << tipo << endl;
			exit(EXIT_FAILURE);
		}
		in >> tipo;
	}
}

// Anade un objeto a la lista de objetos
void addObjeto(Objeto* objeto) {
	objetos.push_back(objeto);
}

// Anade una luz a la lista de luces
void addLuz(Luz* luz) {
	luces.push_back(luz);
}
