
CC = gcc
GLUT = -lGL -lGLU -lglut
FLATS = -lm

main: P01.o figuras.o
	$(CC) -o main P01.o figuras.o $(GLUT) $(FLATS)

P01.o: P01.c figuras.h
	$(CC) -c P01.c

figuras.o: figuras.h figuras.c
	$(CC) -c figuras.c

rm: 
	rm *.o
