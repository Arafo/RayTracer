#include<iostream>
#include <vector>
#include <ctime>

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
const char *FICHERO_BMP = "../resultados/imagen.bmp";
const char *FICHERO_PPM = "../resultados/imagen.ppm";

std::vector<Objeto*> objetos;
std::vector<Luz*> luces;

// Funciones
void addObjeto(Objeto* objeto);
void addLuz(Luz* luz);
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

int main() {

	clock_t t1, t2;
	t1 = clock();

	int w = 512;
	int h = 512;

	Imagen imagen(w, h);
	Camara camara(Vector(0, 20, 100), Vector(0.0, 14, 0.0), Vector(0.0, 1.0, 0.0), 60);

	int columnas = 0;

	// Texturas
	//Textura tex1("../texturas/mapa_hd.ppm");

	// Escena
	/*addObjeto(new Esfera(Vector(10, 0, 0), 30, Color(0.721, 0.167, 0.323), 50, -1, -1, 0));
	addObjeto(new Esfera(Vector(10, 80, -200), 30, Color(0.219, 0.352, 0.949), -1, -1, -1, 0));
	addObjeto(new Esfera(Vector(-44, -10, -20), 20, Color(0.7, 0.7, 0.0), 100, 0.4, -1, 0));
	//addObjeto(new Esfera(Vector(w/4, -1000030, 1000), 1000000, Color(0.211, 0.694, 0.749 ), -1, -1, -1, 0));
	addObjeto(new Esfera(Vector(50, -100030, 0), 100000, Color(0.211, 0.694, 0.749 ), -1, 0.6, -1, 0));

	addLuz(new Luz(Vector(50, 50, 100), 0.9));*/


	// Cornel Box
	/*addObjeto(new Esfera(Vector(16, -22, -300), 16, Color(0, 0, 0), -1, -1, 1.6, 0));
	addObjeto(new Esfera(Vector(-26, -26, -380), 12, Color(0.7, 0.7, 0), 16, -1, -1, 0, tex1));

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
	modelo5.cargar(objetos);*/

	//addLuz(new LuzArea(Vector(0, 20, -350), 0.9, Vector(0, 0, 1), Vector(1, 0, 0), 3));
	//addLuz(new Esfera(Vector(0, 20, -350), 10, 0.9));
	
	//addObjeto(new Caja(Vector(-51, -40, -200), Vector(-50, 40, -500), Color(1, 0.32, 0.32), -1, -1, -1, 0));
	//addObjeto(new Caja(Vector(-40, -40, -400), Vector(50, 40, -401), Color(0.9, 0.9, 0.9), -1, -1, -1, 0));

	//addObjeto(new Plano(Vector(0, 0, -1), 1, Color(0.9, 0, 0.9), -1, -1, -1, 0));

	// Otra escena
	/*addObjeto(new Esfera(Vector(-200, -25, 0), 100, Color(1, 0, 0), 100, 0.75, 0, 0));
	addObjeto(new Esfera(Vector(200, -25, 0), 100, Color(0, 1, 0), 100, 0.75, 0, 0));
	addObjeto(new Esfera(Vector(0, 325, 0), 100, Color(0, 0, 1 ), 100, 0.75, 0, 0));

	addLuz(new Luz(Vector(0, 100, 200), 0.5));*/

	// Escena textura
	/*Camara camara(Vector(100, 0, 0), Vector(80, 0, -80), Vector(0, 1, 0), 60);
	addObjeto(new Esfera(Vector(0, 0, -380), 30, Color(0.7, 0.7, 0), -1, -1, -1, 0, tex1));
	addObjeto(new Esfera(Vector(w/4, -100030, 1000), 100000, Color(0.25, 0.77, 1), -1, -1, 0, 0));	// Suelo
	addLuz(new Luz(Vector(0, 40, -200), 0.9));
	addLuz(new Luz(Vector(0, 40, -400), 0.9));*/

	// Escena componente difusa
	//addObjeto(new Esfera(Vector(-26, -10, -380), 40, Color(0.32, 0.32, 1), -1, -1, -1, 0));
	//addObjeto(new Esfera(Vector(44, -10, -380), 24, Color(1, 0.32, 0.32), -1, -1, -1, 0));
	//addLuz(new Luz(Vector(40, 40, -300), 0.9));

	// Escena componente difusa
	//addObjeto(new Esfera(Vector(-26, -10, -380), 40, Color(0.32, 0.32, 1), -1, -1, -1, 0));
	//addObjeto(new Esfera(Vector(20, 0, -340), 10, Color(1, 0.32, 0.32), -1, -1, -1, 0));
	//addLuz(new Luz(Vector(60, 0, -300), 0.9));

	// Escena componente especular
	//addObjeto(new Esfera(Vector(-26, -10, -380), 40, Color(0.32, 0.32, 1), -1, 0.4, -1, 0));
	//addObjeto(new Esfera(Vector(44, -10, -380), 24, Color(1, 0.32, 0.32), -1, 0.8, -1, 0));
	//addLuz(new Luz(Vector(40, 40, -300), 0.9));

	// Escena reflexion
	//addObjeto(new Esfera(Vector(-26, 0, -400), 40, Color(0.32, 0.32, 1), -1, 0.4, -1, 0));
	//addObjeto(new Esfera(Vector(36, -10, -300), 20, Color(1, 0.32, 0.32), -1, -1, -1, 0));
	//addLuz(new Luz(Vector(0, 40, -200), 0.9));
	//addObjeto(new Esfera(Vector(w/4, -100030, 1000), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));	// Suelo

	// Escena refraccion
	/*addObjeto(new Esfera(Vector(16, -22, -240), 16, Color(0, 0, 0), -1, -1, 1.6, 0));
	addObjeto(new Esfera(Vector(0, -26, -300), 12, Color(0.7, 0.7, 0.32), -1, -1, -1, 0));

	addObjeto(new Esfera(Vector(w/4, -100030, 1000), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));	// Suelo
	addObjeto(new Esfera(Vector(-100038, 0, 1000), 100000, Color(1, 0.32, 0.32), -1, -1, 0, 0));	// Pared Izquierda
	addObjeto(new Esfera(Vector(100038, 0, 1000), 100000, Color(0.55, 0.76, 0.29), -1, -1, 0, 0));	// Pared Derecha
	addObjeto(new Esfera(Vector(w/4, 0, -100340), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));		// Pared Fondo
	addObjeto(new Esfera(Vector(w/4, 100040, 1000), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));	// Techo
	addLuz(new Luz(Vector(0, 20, -250), 0.9));*/

	// Escena Montecarlo (64 muestras)
	//addObjeto(new Esfera(Vector(0, 0, -300), 30, Color(1, 1, 1), -1, -1, -1, 0));
	//addObjeto(new Esfera(Vector(w/4, -100030, 1000), 100000, Color(0.55, 0.76, 0.29), -1, -1, 0, 0));	// Suelo
	//addLuz(new Luz(Vector(0, 100, -100), 0.9));

	// Escena modelos
	Modelo modelo("../modelos/apple.ply", 100, Vector(0, 0, -200), Color(1, 0.32, 0.32));
	modelo.cargar(objetos);
	addObjeto(new Esfera(Vector(w/4, -100030, 1000), 100000, Color(0.32, 0.32, 1), -1, -1, 0, 0));	// Suelo
	addObjeto(new Esfera(Vector(-100038, 0, 1000), 100000, Color(1, 0.32, 0.32), -1, -1, 0, 0));	// Pared Izquierda
	addObjeto(new Esfera(Vector(100038, 0, 1000), 100000, Color(0.32, 1, 0.32), -1, -1, 0, 0));	// Pared Derecha
	addObjeto(new Esfera(Vector(w/4, 0, -100340), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));		// Pared Fondo
	addObjeto(new Esfera(Vector(w/4, 100040, 1000), 100000, Color(0.9, 0.9, 0.9), -1, -1, 0, 0));	// Techo
	addLuz(new Luz(Vector(0, 20, -100), 0.9));


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
	imagen.saveBMP(FICHERO_BMP);
	//imagen.savePPM(FICHERO_PPM);

	t2 = clock();
	float tiempo = ((float)t2 - (float)t1) / 1000;
	cout << endl << "Tiempo: " << tiempo << " segundos" << endl;

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
	return color * 0.2;
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
				colorDifuso = (colorDifuso + (color * producto)) * luz->intensidad;
				colorEspecular = colorEspecular + calcularLuzEspecular(interseccion, luz);
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
    float cosTheta = sqrt(1.0 - r1);
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

//
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

//
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

// Añade un objeto a la lista de objetos
void addObjeto(Objeto* objeto) {
	objetos.push_back(objeto);
}

// Añade una luz a la lista de luces
void addLuz(Luz* luz) {
	luces.push_back(luz);
}