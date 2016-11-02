CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		ray-trace.o Vector.o Imagen.o Color.o Rayo.o Camara.o Interseccion.o Objeto.o Esfera.o Luz.o

LIBS =

TARGET =	ray-trace.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
