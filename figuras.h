//Proyecto P01 Aplicación de dibujo asistidopor computadora
#ifndef _FIGURAS_H_
#define _FIGURAS_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define WALTO  700
#define WANCHO  700
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

//para interface.
typedef struct PUNTOS{
  GLdouble X,Y;
}PUNTOS;

typedef struct LINEA{
  GLdouble Xi;
  GLdouble Yi;
  GLdouble Xf;
  GLdouble Yf;
}LINEA;

typedef struct CUADRADO{
  GLdouble X,Y;
  GLfloat Lado;
}CUADRADO;


typedef struct RECTANGULO{
  GLdouble X,Y;
  GLfloat ancho;
  GLfloat alto;
}RECTANGULO;

typedef struct POLIGONO{
  unsigned char NLados;
  PUNTOS *V;
}POLIGONO;

typedef struct CIRCULO{
  GLfloat x0;
  GLfloat y0;
  GLfloat r;
}CIRCULO;


typedef struct ELIPSE{
  GLfloat x0;
  GLfloat y0;
  GLfloat a,b,th,r;
}ELIPSE;

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
  GLint grosor;
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
//________________________________inteface.
void linea_(LINEA *l);
void cuadrado_(CUADRADO *C);
void rectangulo_(RECTANGULO *R);
void poligonoi_(POLIGONO *P);
void circulo_(CIRCULO *C);
void elipse_(ELIPSE *E);
//________________________________dibujado o cambio de valiables.
void AsignaColor(COLOR color);
void DibujarTexto(char *Text,float x,float y);
void DibujarSelect();
void DibujarIndex();
void Cambio();
void dibujarFiguras();
void init(void);
void DrawInterface(void);//Dibujo de Interface
void Selection(int x,int y); //Seleccion de Color
//________________________________callbacks
void display(void);
void displayView(GLsizei w,GLsizei h);
//void ControlMovimientoRaton( GLsizei x, GLsizei y );
void TeclaEspecial(GLint key,GLint x, GLint y);
void Raton(GLint x,GLint y);
void RatonActivo(GLint x,GLint y);
void ControlRaton( GLint button, GLint state, GLint x, GLint y );
void ControlTeclado( unsigned char key, GLint x, GLint y );
void cierre();

#endif
