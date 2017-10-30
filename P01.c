//Proyecto P01 Aplicación de dibujo asistidopor computadora
#include "figuras.h"//linux

int main(int argc, char** argv)
{
  //Configuraciones Iniciales
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100); //Posicion de la Ventana
  glutInitWindowSize(WANCHO,WALTO); //Tamaño de la Ventana
  glutCreateWindow("PRIMITIVAS PAINT"); //Creacion de la Ventana y su Nombre
//inicialisa las variables.
  init();
 //Asignacion de Callbacks
  glutDisplayFunc(&display); //Asignacion de Callbacks
  glutKeyboardFunc(&ControlTeclado );//controd de teclado
  glutMouseFunc(&ControlRaton );//control mouse
  glutMotionFunc(&RatonActivo);
  atexit(&cierre);
  glutSpecialFunc(&TeclaEspecial);
  glutPassiveMotionFunc(&Raton);
  glutReshapeFunc(&displayView); //Cambia el tamaño del ViewPoint
  //Estado de Espera de Eventos
  glutMainLoop();
  return 0;
}

