CXXFLAGS =	-O3 -g -Wall -fmessage-length=0 -fopenmp

OBJS =		ray-trace.o Vector.o Imagen.o Color.o Rayo.o Camara.o Interseccion.o Objeto.o Esfera.o Luz.o Triangulo.o Modelo.o Textura.o

LIBS =

TARGET =	ray-trace.exe

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
