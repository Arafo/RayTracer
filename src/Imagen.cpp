#include "Imagen.h"

// Constructor
Imagen::Imagen(int width, int height) {
    _width = width;
    _height = height;
    _imagen = (Color*)malloc(sizeof(Color) * _width * _height);
}

// Destructor
Imagen::~Imagen() {
    free(_imagen);
}

// Guarda la imagen almacenada en <_imagen> en el fichero indicado por el
// puntero <fichero> con formato .bmp
void Imagen::saveBMP(const char *fichero) {
	FILE *f;
	int k = _width * _height;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int dpi = 72;
	int ppm = dpi * m;

	unsigned char bmpfileheader[14] = {'B','M',0,0,0,0,0,0,0,0,54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0,0,0,0,0,0,0,0,0,1,0,24,0};

	bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(_width);
	bmpinfoheader[5] = (unsigned char)(_width >> 8);
	bmpinfoheader[6] = (unsigned char)(_width >> 16);
	bmpinfoheader[7] = (unsigned char)(_width >> 24);

	bmpinfoheader[8] = (unsigned char)(_height);
	bmpinfoheader[9] = (unsigned char)(_height >> 8);
	bmpinfoheader[10] = (unsigned char)(_height >> 16);
	bmpinfoheader[11] = (unsigned char)(_height >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(s);
	bmpinfoheader[30] = (unsigned char)(s >> 8);
	bmpinfoheader[31] = (unsigned char)(s >> 16);
	bmpinfoheader[32] = (unsigned char)(s >> 24);

	f = fopen(fichero, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
        	Color* rgb = _imagen + (x * _height + y);

        	float red = (rgb->r) * 255;
			float green = (rgb->g) * 255;
			float blue = (rgb->b) * 255;

			unsigned char color[3] = {(int)floor(blue), (int)floor(green), (int)floor(red)};
			fwrite(color, 1, 3, f);
		}
	}

	fclose(f);
}

// Guarda la imagen almacenada en <_imagen> en el fichero indicado por el
// puntero <fichero> con formato .ppm
void Imagen::savePPM(const char *fichero) {
	FILE *f = fopen(fichero, "wb");
	fprintf(f, "P6\n%d %d\n255\n", _width, _height);

	for (int y = _height - 1; y >= 0; y--) {
        for (int x = 0; x < _width; x++) {
    		Color* rgb = _imagen + (x * _height + y);

        	float red = (rgb->r) * 255;
			float green = (rgb->g) * 255;
			float blue = (rgb->b) * 255;

    		unsigned char color[3] = {(int)floor(red), (int)floor(green), (int)floor(blue)};
			fwrite(color, 1, 3, f);
		}
	}
	fclose(f);
}

// Pinta en las coordenadas (x, y) el Color <color> en la imagen.
void Imagen::pintar(int x, int y, Color color) {
    if (x < 0 || x > _width - 1 || y < 0 || y > _height - 1) {

    }
    
    _imagen[x * _height + y] = color;
}