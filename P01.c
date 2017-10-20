#include "figuras.h"//linux

int main(int argc, char** argv)
{
  //Configuraciones Iniciales
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100); //Posicion de la Ventana
  glutInitWindowSize(ANCHO,ALTO); //Tamaño de la Ventana(500,500)
  glutCreateWindow("PRIMITIVAS PAINT"); //Creacion de la Ventana y su Nombre
//inicialisa las variables.
  init();
 //Asignacion de Callbacks
  glutDisplayFunc(&display); //Asignacion de Callbacks
  glutKeyboardFunc(&ControlTeclado );//controd de teclado
  glutMouseFunc(&ControlRaton );//control mouse
  //glutMotionFunc(&ControlMovimientoRaton );
  //glutMotionFunc();
  glutCloseFunc(&cierre);
  glutPassiveMotionFunc(&Raton);
  glutReshapeFunc(&displayView); //Cambia el tamaño del ViewPoint
  //Estado de Espera de Eventos
  glutMainLoop();
  return 0;
}
