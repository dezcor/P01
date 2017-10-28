//Proyecto P01 Aplicación dedibujo asistidopor computadora
#ifndef _FIGURAS_H_
#define _FIGURAS_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define ALTO 500
#define ANCHO 500
//________________________________Paleta de colores.
typedef enum{
  NEGRO,
  ZAFIRO,
  AZUL,
  VERDE_KELLY,
  TRUQUESA,
  AZUL_CLARO,
  VERDE,
  VERDE_BAJO,
  CYAN,
  ROJO_OSCURO,
  FUCSIA,
  MORADO,
  LIMA,
  GRIS,
  CELESTE,
  CHARTREUSE,
  VERDE_AGUA,
  CYAN_BAJO,
  ROJO,
  ROSA,
  VIOLETA,
  NARANJA,
  SALMON,
  MALVA,
  AMARILLO,
  MARFIL,
  BLANCO
}COLOR;

//identificador de figura.
typedef enum{
  TYPELINEA,
  TYPECUADRADO,
  TYPERECTAGULO,
  TYPEPOLIGONOI,
  TYPECIRCULO,
  TYPEELIPSE
}TYPO_FIGURA;
//________________________________estructura de lista de puntos.
typedef struct punto
{
    GLdouble X,Y;
    struct punto *next;
}PUNTO;
//________________________________ estrctura de la lista.
typedef struct lista{
  PUNTO * V;
  GLint Nv;
  char STIPPLE;
  GLint Nx;
  COLOR color;
  TYPO_FIGURA type;
  struct lista *next;
}LISTA;
//________________________________estrcutura para guardar index y lista asi como contar las figuras.
typedef struct figuras{
    int numero;
  LISTA *index;
  LISTA *Plist;
}FIGURAS;
//________________________________dibujado seleccion.
typedef struct dibujado{
    void (*Dibujar)(LISTA* list);
}DIBUJADO;
//________________________________listaPuntos
void setlistP(GLint,GLint);
void liberar(PUNTO *);
//________________________________listaFiguras.
void setlist(LISTA* list);

//________________________________funciones para el dibujado de figuras.
void linea(LISTA* list);
void cuadrado(LISTA* list);
void rectangulo(LISTA* list);
void poligonoi(LISTA* list);
void circulo(LISTA* list);
void elipse(LISTA* list);
//________________________________dibujado o cambio de valiables.
void AsignaColor(COLOR color);
void DibujarSelect();
void DibujarIndex();
void Cambio();
void dibujarFiguras();
void init(void);
//________________________________callbacks
void display(void);
void displayView(GLsizei w,GLsizei h);
//void ControlMovimientoRaton( GLsizei x, GLsizei y );
void Raton(int x,int y);
void ControlRaton( GLint button, GLint state, GLint x, GLint y );
void ControlTeclado( unsigned char key, GLint x, GLint y );
void cierre();

#endif
