#ifndef _FIGURAS_H_
#define _FIGURAS_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define ALTO 500
#define ANCHO 500

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


typedef enum{
  TYPELINEA,
  TYPECUADRADO,
  TYPERECTAGULO,
  TYPEPOLIGONOI,
  TYPECIRCULO,
  TYPEELIPSE
}TYPO_FIGURA;
//Paleta de colores.
typedef struct punto
{
    GLdouble X,Y;
    struct punto *next;
}PUNTO;

typedef struct lista{
  PUNTO * V;
  GLint Nv;
  char STIPPLE;
  GLint Nx;
  COLOR color;
  TYPO_FIGURA type;
  struct lista *next;
}LISTA;
typedef struct figuras{
    int numero;
  LISTA *index;
  LISTA *Plist;
}FIGURAS;
//dibujado
typedef struct dibujado{
    void (*Dibujar)(LISTA* list);
}DIBUJADO;
//listaPuntos
void setlistP(GLint,GLint);
void liberar(PUNTO *);
//listaFiguras.
void setlist(LISTA* list);
//Funciones de dibujado.

void linea(LISTA* list);
void cuadrado(LISTA* list);
void rectangulo(LISTA* list);
void poligonoi(LISTA* list);
void circulo(LISTA* list);
void elipse(LISTA* list);
void display(void);
void AsignaColor(COLOR color);
void DibujarSelect();
void displayView(GLsizei w,GLsizei h);
//void ControlMovimientoRaton( GLsizei x, GLsizei y );
void Raton(int x,int y);
void DibujarIndex();
void Cambio();
void ControlRaton( GLint button, GLint state, GLint x, GLint y );
void ControlTeclado( unsigned char key, GLint x, GLint y );
void dibujarFiguras();
void cierre();
void init(void);

#endif
