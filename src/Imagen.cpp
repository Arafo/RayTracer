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

        	float red = (rgb->r > 1.0) ? 1.0 : rgb->r;;
			float green = (rgb->g > 1.0) ? 1.0 : rgb->g;
			float blue = (rgb->b > 1.0) ? 1.0 : rgb->b;

    		unsigned char color[3] = {
    			static_cast<unsigned char>((int)floor(blue * 255)),
    			static_cast<unsigned char>((int)floor(green * 255)),
    			static_cast<unsigned char>((int)floor(red * 255))};
			fwrite(color, 1, 3, f);
		}
	}

	fclose(f);
}

// Lee la imagen en el fichero indicado por el puntero <fichero>
// con formato .bmp y la almacena en <_imagen> 
void Imagen::readBMP(const char* fichero) {
    FILE* f = fopen(fichero, "rb");

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    _width = width;
    _height = height;
    _imagen = (Color*)malloc(sizeof(Color) * _width * _height);

    unsigned char* data = new unsigned char[3];

	for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x += 1) {
        	fread(data, 1, 3, f);
            _imagen[x * _height + y] = Color(
            	(float)((int)data[2]) / 255.0f, 
            	(float)((int)data[1]) / 255.0f, 
            	(float)((int)data[0]) / 255.0f);
        }
    }
    fclose(f);
}

// Guarda la imagen almacenada en <_imagen> en el fichero indicado por el
// puntero <fichero> con formato .ppm
void Imagen::savePPM(const char *fichero, string tiempo) {
	FILE *f = fopen(fichero, "wb");
	fprintf(f, "P6\n");

    if (!tiempo.empty())
        fprintf(f, "#%s\n", tiempo.c_str());

    fprintf(f, "%d %d\n255\n", _width, _height);

	for (int y = _height - 1; y >= 0; y--) {
        for (int x = 0; x < _width; x++) {
    		Color* rgb = _imagen + (x * _height + y);

        	float red = (rgb->r > 1.0) ? 1.0 : rgb->r;;
			float green = (rgb->g > 1.0) ? 1.0 : rgb->g;
			float blue = (rgb->b > 1.0) ? 1.0 : rgb->b;

    		unsigned char color[3] = {
    			static_cast<unsigned char>((int)floor(red * 255)),
    			static_cast<unsigned char>((int)floor(green * 255)),
    			static_cast<unsigned char>((int)floor(blue * 255))};
    		fwrite(color, 1, 3, f);
		}
	}
	fclose(f);
}

// Lee la imagen en el fichero indicado por el puntero <fichero>
// con formato .ppm y la almacena en <_imagen> 
void Imagen::readPPM(const char *fichero) {
    int width = 0, height = 0, maxColor = 0;

    FILE* f;
	if ((f = fopen(fichero, "rb")) == 0) {
		fprintf(stderr, "Error al abrir fichero: %s\n", fichero);
    	exit(1);
	}

    // Cabezera P6
    char buff[16];
    if (!fgets(buff, sizeof(buff), f)) {
    	perror(fichero);
    	exit(1);
    }

    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Formato no valido\n");
         exit(1);
    }

    // Comentarios
    int c = getc(f);
    while (c == '#') {
    while (getc(f) != '\n') ;
         c = getc(f);
    }
    ungetc(c, f);

    fscanf(f, "%d %d", &width, &height);
    fscanf(f, "%d", &maxColor);
    while (fgetc(f) != '\n') ;

    _width = width;
    _height = height;
    _imagen = (Color*)malloc(sizeof(Color) * _width * _height);   
    
    cout << "Textura: " << fichero << ", ";
	cout << "W: " << width << ", ";
	cout << "H: " << height << endl;

    unsigned char* data = new unsigned char[3];

	for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
        	fread(data, 1, 3, f);
            _imagen[x * _height + y] = Color(
            	(float)((int)data[0]) / 255.0f, 
            	(float)((int)data[1]) / 255.0f, 
            	(float)((int)data[2]) / 255.0f);
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

int Imagen::getWidth() {
	return _width;
}

int Imagen::getHeight() {
	return _height;
}

Color *Imagen::getImagen() {
	return _imagen;
}
