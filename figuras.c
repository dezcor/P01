//Proyecto P01 Aplicación dedibujo asistidopor computadora
#include "figuras.h"
GLfloat xpos=0, zpos=0,next=0;
//Paleta de Colores
const GLdouble PaletaColor[27][3]={
    {0,0,0},
    {0,0,0.5},
    {0,0,1},
    {0,0.5,0},
    {0,0.5,0.5},
    {0,0.5,1},
    {0,1,0},
    {0,1,0.5},
    {0,1,1},
    {0.5,0,0},
    {0.5,0,0.5},
    {0.5,0,1},
    {0.5,0.5,0},
    {0.5,0.5,0.5},
    {0.5,0.5,1},
    {0.5,1,0},
    {0.5,1,0.5},
    {0.5,1,1},
    {1,0,0},
    {1,0,0.5},
    {1,0,1},
    {1,0.5,0},
    {1,0.5,0.5},
    {1,0.5,1},
    {1,1,0},
    {1,1,0.5},
    {1,1,1}
};
//_________________________________________________________Variables Globles
FIGURAS Figuras;
//para ver si hay figura en proceso. 0 indica que no es asi.
int pushRaton=0;
//para dibujara el posible punto.
GLdouble m_x, m_y;
//color seleccionado global una ves que se guarada la figura el color no es modificable.
COLOR color;
//vector para seleccionar la figura a dibujar.
DIBUJADO FiguraSelecionada[6];
//valiables del glortho2D
GLfloat xmin=-10,xmax=10,ymin=-10,ymax=10;
//Escalares para el tamaño de la pantalla.
GLfloat Px,Py,esclaOrtoX=1;
//Figura seleccionada.
TYPO_FIGURA select_f;
//Para el tipo de lineado
GLint Ax,Bx,Cx,Dx,Nx;
//Activar o desactivar el STIPPLE.
char STIPPLE=0;
void display()
{
  glClear (GL_COLOR_BUFFER_BIT);//Seleccionar buffer a limpear
  glClearColor(PaletaColor[NEGRO][0],PaletaColor[NEGRO][1],PaletaColor[NEGRO][2],0); //Color de la Ventana
  dibujarFiguras();//Dibujar Figuras
  DibujarIndex();//Figura seleccionada
  DibujarSelect();//algo quitar de aqui
  glFlush();
}

void dibujarFiguras()
{
  if(Figuras.Plist==NULL)return;//Si no hay valores en la lista termina
  LISTA *star;//puntero para recorrer la lista enlazada.
  star=Figuras.Plist;//se toma el inicio en una valiable aparte. para recorrer la lista enlazada
  while(star!=NULL)//mientras star sea diferente de NULL segura en el siclo.
  {
    glLineWidth(1.0);
    if(star->STIPPLE) glEnable(GL_LINE_STIPPLE);//Estilo de dibujado habilidado o desabilidado dependiendo de la figura.
    glLineStipple(1,star->Nx); //estilo de la linea.
    FiguraSelecionada[star->type].Dibujar(star);//figura a dibujar.
    if(star->STIPPLE)glDisable(GL_LINE_STIPPLE); // DESHABILITAMOS LA PROPIEDAD STIPPLE si esta fue habilitada.
    star=star->next;//siguiente figura.
  }
}
//Dibujado de una liena.
void linea(LISTA* list)
{
    AsignaColor(list->color);//Asignacion del color de la figura.
    glBegin(GL_LINES);//primitiva GL_LINES
    glVertex2f(list->V[0].X,list->V[0].Y);//punto inicio
    glVertex2f(list->V[1].X,list->V[1].Y);//punto final.
    glEnd();//termino de primitiva.
}
//Dibujado de cuadrado.
void cuadrado(LISTA* list)
{
    AsignaColor(list->color);
    GLdouble th=0,x,y,r,th_r=3.1415/180;
    x=(list->V[0].X-list->V[1].X);//distania entre x incial y x final
    y=(list->V[0].Y-list->V[1].Y);//distania entre y incial e y final
    r=sqrt(x*x+y*y);//radio
    glBegin(GL_LINE_LOOP);//Primitiva GL_LINE_LOOP para que se una el punto final con el inicial.
    for(th=-45;th<=315;th+=90) //inicia en -45 grados y cada 90 grados se pone un punto. hasta 315 grados.
    {
        x=r*cos(th*th_r)+list->V[0].X;
        y=r*sin(th*th_r)+list->V[0].Y;
        glVertex2f(x,y);
    }
    glEnd();//termina la primitiva
}
//Dibujado del rectangulo.
void rectangulo(LISTA* list)
{
    AsignaColor(list->color);//Asignacion de Color
    glBegin(GL_LINE_LOOP);//Primitiva GL_LINE_LOOP para que se una el punto final con el inicial.
    glVertex2f(list->V[0].X,list->V[0].Y);//Punto inicial.
    glVertex2f(list->V[0].X,list->V[1].Y);//x inicial mas y final.
    glVertex2f(list->V[1].X,list->V[1].Y);//Punto final.
    glVertex2f(list->V[1].X,list->V[0].Y);//x final mas y inicial.
    glEnd();//termina la primitiva
}

//Dibujado de Poligono Irregular.
void poligonoi(LISTA* list)
{
    int i=0;
    AsignaColor(list->color);//Asignacion de Color
    glBegin(GL_LINE_LOOP);//Primitiva GL_LINE_LOOP para que se una el punto final con el inicial.
    for(i=0;i<list->Nv;i++)
    {
        glVertex2f(list->V[i].X,list->V[i].Y);//se recorre el vector para formar el poligono.
    }
    glEnd();//termina la primitiva.
}

//Dibujado de circulo.
void circulo(LISTA* list)
{
    AsignaColor(list->color);//Asignacion de Color
    GLdouble th=0,x,y,r,th_r=3.1415/180;
    x=(list->V[0].X-list->V[1].X);//distania entre x incial y x final
    y=(list->V[0].Y-list->V[1].Y);//distania entre y incial e y final
    r=sqrt(x*x+y*y);//radio del circulo.
    glBegin(GL_LINE_LOOP);//Primitiva GL_LINE_LOOP para que se una el punto final con el inicial.
    for(th=0;th<360;th+=1)
    {
        x=r*cos(th*th_r)+list->V[0].X;//se suma el centro. con esto se le da el punto de localizacion.
        y=r*sin(th*th_r)+list->V[0].Y;
        glVertex2f(x,y);
    }
    glEnd();//Termina la primitiva
}

//Dibujado de elipse
void elipse(LISTA* list)
{
    AsignaColor(list->color);//Asignacion de Color
    GLdouble th=0,x,y,x1,y1,a,b,th_r=3.1415/180;
    a=fabs(list->V[0].X-list->V[1].X)/2;//la mita de la distancia de x inicial y x final
    b=fabs(list->V[0].Y-list->V[1].Y)/2;//la mita de la distancia de y inicial e y final
    x1=(list->V[0].X+list->V[1].X)/2;//el centro se localiza a la mita tanto de x como de y;
    y1=(list->V[0].Y+list->V[1].Y)/2;
    glBegin(GL_LINE_LOOP);//Primitiva GL_LINE_LOOP para que se una el punto final con el inicial.
    for(th=0;th<360;th+=1)
    {
        x=a*cos(th*th_r)+x1;
        y=b*sin(th*th_r)+y1;
        glVertex2f(x,y);
    }
    glEnd();
}

//Asignacion de color mediante una paleta de colores.
inline void AsignaColor(COLOR color)
{
    glColor3f(PaletaColor[color][0],PaletaColor[color][1],PaletaColor[color][2]);
}

//Eventos del raton. bontones.
void ControlRaton( int button, int state, int x, int y )
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)//click sobre boton izquierdo  
    {
        pushRaton=1;//badera de que se iniciado una figura. Esta se usa para dibujara la pre-figura.
        setlistP(x,y);//se agrega el punto a una lista enlazada de puntos.
        if ((Figuras.index->type!=TYPEPOLIGONOI)&&Figuras.index->Nv==2)//mientras no sea la figura poligono esta terminara cuando la lista llegue a 2 puntos.
        {
            pushRaton=0;//bandera de termino la figura.
            setlist(Figuras.index);//se manda la figura a la lista enlazada de figuras.
        }

        glutPostRedisplay();//se manda redibujar.
    }
    if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//Este evento se usa para terminara el poligono.
    {
        if(Figuras.index!=NULL)//si no hay poligono aun no hace nada.
        if ((Figuras.index->type==TYPEPOLIGONOI))
        {
            pushRaton=0;//cambio de bandera de pushRaton a para decir que no hay figura para el pre-dibujado de esta.
            setlistP(x,y);//se agrega el punto a una lista enlazada de puntos.
            setlist(Figuras.index);//se manda la figura a la lista enlazada de figuras.
            glutPostRedisplay();//se manda redibujar.
        }
    }
}

void ControlTeclado(unsigned char key,int x,int y ){
    /* Según la tecla pulsada incremento una u otra variable de movimiento */
    switch(key){
        case 'd': case 'D':
            STIPPLE=!STIPPLE;
            break;
        case 'z': case 'Z':
            select_f=TYPELINEA;
            break;
        case 'x': case 'X':
            select_f=TYPECUADRADO;
            break;
        case 'c': case 'C':
            select_f=TYPERECTAGULO;
            break;
        case 'v': case 'V':
            select_f=TYPEPOLIGONOI;
            break;
        case 'b': case 'B':
            select_f=TYPECIRCULO;
            break;
        case 'n': case 'N':
            select_f=TYPEELIPSE;
            break;
        case 'a': case 'A':
            if(color<BLANCO)
                color+=1;
            break;
        case 's': case 'S':
            if(color>NEGRO)
                color-=1;
            break;
        case 'q': case 'Q':
            if(Ax<0xf)
                Ax++;
            else if(Ax==0xf)
                Ax=0;
            Nx=Ax*pow(16,3)+Bx*pow(16,2)+Cx*16+Dx;
            break;
        case 'w': case 'W':
             if(Bx<0xf)
                Bx++;
             else if(Bx==0xf)
                Bx=0;
             Nx=Ax*pow(16,3)+Bx*pow(16,2)+Cx*16+Dx;
            break;
        case 'e': case 'E':
             if(Cx<0xf)
                Cx++;
             else if(Cx==0xf)
                Cx=0;
             Nx=Ax*pow(16,3)+Bx*pow(16,2)+Cx*16+Dx;
            break;
        case 'r': case 'R':
             if(Dx<0xf)
                Dx++;
             else if(Dx==0xf)
                Dx=0;
             Nx=Ax*pow(16,3)+Bx*pow(16,2)+Cx*16+Dx;
            break;
                }
    /* Le digo a OpenGL que dibuje de nuevo cuando pueda */
    Cambio();
    glutPostRedisplay( );
}

//inicializacion de la valiables glovales.
inline void init(void)
{
    Figuras.index=NULL;
    Figuras.Plist=NULL;
    Figuras.numero=0;
    select_f=TYPELINEA;
    color=ZAFIRO;
    STIPPLE=0;
    Nx=0xFFFF;
    Ax=0xF;
    Bx=0XF;
    Cx=0XF;
    Dx=0XF;
    Px=ANCHO/(xmax-xmin),Py=ALTO/(ymax-ymin);
    //Se asignan las funciones de dibujado.
    FiguraSelecionada[TYPELINEA].Dibujar=linea;
    FiguraSelecionada[TYPECUADRADO].Dibujar=cuadrado;
    FiguraSelecionada[TYPERECTAGULO].Dibujar=rectangulo;
    FiguraSelecionada[TYPEPOLIGONOI].Dibujar=poligonoi;
    FiguraSelecionada[TYPECIRCULO].Dibujar=circulo;
    FiguraSelecionada[TYPEELIPSE].Dibujar=elipse;
}

//Al termino de la aplicacion LIberacion de la memoria de cada figura creada asi como de los vectores. 
void cierre()
{
    printf("Cierre: Numero de figuras %d\n",Figuras.numero);//numero de figuras creadas.
    if(Figuras.index!=NULL)// hay una figura en creacion se libera.
    {
        liberar(Figuras.index->V);//liberacion de lista de puntos.
        free(Figuras.index);//liberacion de la figura. 
    }
    if(Figuras.Plist==NULL)return;// Si no hay figuras termina.
    LISTA *aux;
    while(Figuras.Plist->next!=NULL)
    {
        free(Figuras.Plist->V);//liberacion del vector.
        aux=Figuras.Plist;//guarda la figura actual.
        Figuras.Plist=Figuras.Plist->next;//Avanza a la siguiente figura.
        free(aux);//libera la figura guardada.
    }
}

//Ingresar Figura en lista enlazada.
void setlist(LISTA* list)
{
    int i=0;
    Figuras.numero++;//aumenta  numero de figuras.
    if(Figuras.Plist==NULL)
    {
        Figuras.Plist=list;
        Figuras.Plist->next=NULL;
        PUNTO *aux,*Vector;
        aux=list->V;
        //Creacion del vector de puntos.
        Vector=(PUNTO*)malloc(sizeof(PUNTO)*list->Nv);
        for(i=0;i<list->Nv;i++)
        {
            Vector[i].X=aux->X;
            Vector[i].Y=aux->Y;
            Vector[i].next=NULL;
            aux=aux->next;
        }
        liberar(Figuras.Plist->V);//Liberacion de la lista enlazada de puntos.
        Figuras.Plist->V=Vector;//se asigna el vetor en la figura.
        Figuras.index=NULL;// se iguala a NULL la figura a crear.
        return;
    }
    else
    {
        LISTA *aux;
        aux=Figuras.Plist;
        while(aux->next!=NULL)//recorre la lista hasta encontrar la ultima figura.
        {
            aux=aux->next;
        }
        
        aux->next=list;
        aux->next->next=NULL;
        PUNTO *aux1,*Vector;
        aux1=list->V;
        //Creacion del vector de puntos.
        Vector=(PUNTO*)malloc(sizeof(PUNTO)*list->Nv);
        for(i=0;i<list->Nv;i++)
        {
            Vector[i].X=aux1->X;
            Vector[i].Y=aux1->Y;
            Vector[i].next=NULL;//para identificar que es vector en la liberacion.
            aux1=aux1->next;//avanza al siguente punto.
        }
        liberar(aux->next->V);//Liberacion de la lista enlazada de puntos.
        aux->next->V=Vector;//se asigna el vetor en la figura.
        Figuras.index=NULL;//se iguala a NULL la figura a crear.

    }
}

//Redimencion de la ventana.
void displayView(GLsizei w,GLsizei h)
{
  glViewport(0,0,w,h);
  //escala del Ortho2D en x;
  esclaOrtoX=(GLdouble)w/h;
  //Escalar Ortho2D a tamaño de la pantalla. en x y en y
  Px=w/(xmax*esclaOrtoX-xmin*esclaOrtoX),Py=h/(ymax-ymin);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //redimenion del Ortho2D dependido de el escalar.
  gluOrtho2D(xmin*esclaOrtoX,xmax*esclaOrtoX,ymin,ymax);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//Insercion de punto en lista enlazada.
void setlistP(GLint x, GLint y)
{
    if(Figuras.index==NULL)//Crea la figura si esta no existe.
    {
        Figuras.index=(LISTA*)malloc(sizeof(LISTA));
        Figuras.index->V=NULL;
        Figuras.index->type=select_f;
        Figuras.index->Nv=0;
        Figuras.index->STIPPLE=1;
        Figuras.index->Nx=Nx=0xFFFF;
        Figuras.index->color=color;
    }
        
    if(Figuras.index->V==NULL)//Crea la lista de puntos si esta no existe.
    {
        Figuras.index->V=(PUNTO*)malloc(sizeof(PUNTO));
        Figuras.index->V->next=NULL;
        Figuras.index->V->X=x/Px+xmin*esclaOrtoX;//se convierte el pixel en cordenadas del Ortho2D;
        Figuras.index->V->Y=-y/Py-ymin;//se convierte el pixel en cordenadas del Ortho2D;
        Figuras.index->Nv++;//aumenta el numero de puntos.
        m_x=Figuras.index->V->X;//para el predibujado se inicia en el punto inicial.
        m_y=Figuras.index->V->Y;
        //x/Px+xmin,y/Py-ymin
    }
    else if( Figuras.index->V->next==NULL)//Si ya existe la lista.
    {
        Figuras.index->V->next=(PUNTO*)malloc(sizeof(PUNTO));
        Figuras.index->V->next->next=NULL;
        Figuras.index->V->next->X=x/Px+xmin*esclaOrtoX;
        Figuras.index->V->next->Y=-y/Py-ymin;
        Figuras.index->Nv++;
        m_x=Figuras.index->V->next->X;
        m_y=Figuras.index->V->next->Y;
    }
    else
    {
        PUNTO *aux;
        aux=Figuras.index->V;
        while(aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=(PUNTO*)malloc(sizeof(PUNTO));
        aux->next->next=NULL;
        aux->next->X=x/Px+xmin*esclaOrtoX;
        aux->next->Y=-y/Py-ymin;
        Figuras.index->Nv++;
        m_x=aux->next->X;
        m_y=aux->next->Y;
    }
}

//liberacion de Puntos Vector O lista.
void liberar(PUNTO *V)
{
    if(V==NULL)return;// no hay termina.
    if(V->next==NULL)// si solo es un valor o un vector se libera.
    {
        free(V);
    }
    else
    {
        PUNTO *aux;
        while(V->next!=NULL)// si es lista.
        {
            aux=V;
            free(aux);
            V=V->next;
        }
    }
}

void DibujarSelect()
{
    AsignaColor(color);		//COLOR
	glPointSize(25.0);		//TAMAÑO PUNTO
	glBegin(GL_POINTS);		//DEFINIMOS PRIMITIVA POINTS
	glVertex2f(9,9); 	//DIBUJAMOS PUNTO
	glEnd();
    glEnable(GL_LINE_STIPPLE); // HABILITAMOS LA PROPIEDAD STIPPLE
	glLineWidth(10.0); // ANCHO LINEA
	glLineStipple(3,Nx); // Dash Line ( pixeles por linea, patron linea punteada (HEXADECIMAL))
	glBegin(GL_LINES);
	glVertex2f(-9,9);
	glVertex2f(9,9);
	glEnd();
    glDisable(GL_LINE_STIPPLE);// DESHABILITAMOS LA PROPIEDAD STIPPLE
}

//raton pasivo.
void Raton(int x1,int y1)
{
    if(pushRaton==1)//si se esta creando una figura se pre-dibuja.
    {   //Conversion de cordenadas.
        m_x=x1/Px+xmin*esclaOrtoX;
        m_y=-y1/Py-ymin;
        glutPostRedisplay( );
    }
}

void DibujarIndex()
{
    if(Figuras.index==NULL)return;
    if(pushRaton==0)return;
    int i=0;
    PUNTO *aux,*Vector;
    LISTA *predibujo;
    aux=Figuras.index->V;
    //Creacion del vector +1
    Vector=(PUNTO*)malloc(sizeof(PUNTO)*(Figuras.index->Nv+1));
    for(i=0;i<Figuras.index->Nv;i++)
    {
        Vector[i].X=aux->X;
        Vector[i].Y=aux->Y;
        Vector[i].next=NULL;
        aux=aux->next;
    }
    //Asignacion del ultimo valor en vase a la localizacion del rato.
    Vector[Figuras.index->Nv].X=m_x;
    Vector[Figuras.index->Nv].Y=m_y;
    //creacion de figura previa.
    predibujo=(LISTA*)malloc(sizeof(LISTA));
    //Copeado de los valores de la figura a crear.
    predibujo->V=Vector;   
    predibujo->Nx=Figuras.index->Nx;
    predibujo->Nv=Figuras.index->Nv+1;
    predibujo->color=Figuras.index->color; 
    predibujo->type=Figuras.index->type;
    predibujo->STIPPLE=Figuras.index->STIPPLE;
    //Dibuajdo de la figura.
    glLineWidth(1.0);
    if(predibujo->STIPPLE) glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, predibujo->Nx);
    FiguraSelecionada[predibujo->type].Dibujar(predibujo);
    if(predibujo->STIPPLE)glDisable(GL_LINE_STIPPLE);
    //Liberacion del vector y figura.
    free(predibujo);  
    free(Vector);
}

void Cambio()
{
    //Cambio de valores de la figura.
    if(Figuras.index==NULL)return;//si no existe termina.
    Figuras.index->STIPPLE=STIPPLE;
    Figuras.index->Nx=Nx;
    Figuras.index->color=color;
}