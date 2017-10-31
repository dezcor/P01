//Proyecto P01 Aplicación de dibujo asistidopor computadora
#include "figuras.h"
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
COLOR SelectColor;
//vector para seleccionar la figura a dibujar.
DIBUJADO FiguraSelecionada[6];
//valiables del glortho2D
GLfloat xmin=-10,xmax=10,ymin=-10,ymax=10;
//Escalares para el tamaño de la pantalla.
GLfloat Px,Py;//esclaOrtoX=1;
GLint ALTO=WALTO,ANCHO=WANCHO,SelectedForm=0;
//Figura seleccionada.
TYPO_FIGURA select_f;
//Para el tipo de lineado
GLint Ax,Bx,Cx,Dx,Nx;
//Activar o desactivar el STIPPLE.
GLint Grosor=1;
char Coordenadas[40]="(0,0)";
char TipoLinea[40]="0xFFFF";
char STIPPLE=0;
void display()
{
  glClear (GL_COLOR_BUFFER_BIT);//Seleccionar buffer a limpear
  glClearColor(PaletaColor[BLANCO][0],PaletaColor[BLANCO][1],PaletaColor[BLANCO][2],0); //Color de la Ventana
  dibujarFiguras();//Dibujar Figuras
  DibujarIndex();//Figura seleccionada
  DrawInterface();//Dibujar interface
  glFlush();
}

void dibujarFiguras()
{
  if(Figuras.Plist==NULL)return;//Si no hay valores en la lista termina
  LISTA *star;//puntero para recorrer la lista enlazada.
  star=Figuras.Plist;//se toma el inicio en una valiable aparte. para recorrer la lista enlazada
  while(star!=NULL)//mientras star sea diferente de NULL segura en el siclo.
  {
    glLineWidth(star->grosor);
    if(star->STIPPLE) glEnable(GL_LINE_STIPPLE);//Estilo de dibujado habilidado o desabilidado dependiendo de la figura.
    glLineStipple(1,star->Nx); //estilo de la linea.
    FiguraSelecionada[star->type].Dibujar(star);//figura a dibujar.
    if(star->STIPPLE)glDisable(GL_LINE_STIPPLE); // DESHABILITAMOS LA PROPIEDAD STIPPLE si esta fue habilitada.
    star=star->next;//siguiente figura.
    glLineWidth(1.0);
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
        if((x>=0)&&(x<=ANCHO)&&(y>=0)&&(y<=(ALTO/4)-(0.05*ALTO)))
            Selection(x,y);
        else
        {
            pushRaton=1;//badera de que se iniciado una figura. Esta se usa para dibujara la pre-figura.
            setlistP(x,y);//se agrega el punto a una lista enlazada de puntos.
            if ((Figuras.index->type!=TYPEPOLIGONOI)&&Figuras.index->Nv==2)//mientras no sea la figura poligono esta terminara cuando la lista llegue a 2 puntos.
            {
                pushRaton=0;//bandera de termino la figura.
                setlist(Figuras.index);//se manda la figura a la lista enlazada de figuras.
            }
        }
        glutPostRedisplay();//se manda redibujar.
    }
    if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//Este evento se usa para terminara el poligono.
    {
        if(((x>=0)&&(x<=ANCHO)&&(y>=0)&&(y<=(ALTO/4)-(0.05*ALTO)))==0)
            if(Figuras.index!=NULL)//si no hay poligono aun no hace nada.
                if ((Figuras.index->type==TYPEPOLIGONOI)&&Figuras.index->Nv>=2)
                {
                    pushRaton=0;//cambio de bandera de pushRaton a para decir que no hay figura para el pre-dibujado de esta.
                    setlistP(x,y);//se agrega el punto a una lista enlazada de puntos.
                    setlist(Figuras.index);//se manda la figura a la lista enlazada de figuras.
                    glutPostRedisplay();//se manda redibujar.
                }
    }
}

void ControlTeclado(unsigned char key,int x,int y )
{
    /* Según la tecla pulsada incremento una u otra variable de movimiento */
    switch(key){
        case 'd': case 'D':
            STIPPLE=!STIPPLE;
            break;
        case 'z': case 'Z':
	    SelectedForm=0;
            select_f=TYPELINEA;
            break;
        case 'x': case 'X':
	    SelectedForm=1;
            select_f=TYPECUADRADO;
            break;
        case 'c': case 'C':
	    SelectedForm=2;
            select_f=TYPERECTAGULO;
            break;
        case 'v': case 'V':
	    SelectedForm=3;
            select_f=TYPEPOLIGONOI;
            break;
        case 'b': case 'B':
	   SelectedForm=4;
            select_f=TYPECIRCULO;
            break;
        case 'n': case 'N':
	    SelectedForm=5;
            select_f=TYPEELIPSE;
            break;
        case 'a': case 'A':
            if(SelectColor<BLANCO)
            SelectColor+=1;
            break;
        case 's': case 'S':
            if(SelectColor>NEGRO)
            SelectColor-=1;
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
    sprintf(TipoLinea,"0x%04x",Nx);
    glutPostRedisplay( );
}

void TeclaEspecial(int key,int x, int y)
{
	switch(key)
	{
        case GLUT_KEY_F1 :
            if(Grosor<12)
			    Grosor++;
			break;
		case GLUT_KEY_F2 :
            if(Grosor>0)
                Grosor--;
            break;
        case GLUT_KEY_END:
            cierre();
            init();
            break;
    }
    Cambio();
	glutPostRedisplay();
}

void DibujarTexto(char *Text,float x,float y)
{
    AsignaColor(NEGRO);
	char *c;
	glRasterPos2f(x,y);
	for(c=Text;*c!='\0';c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*c);
    }
}

//inicializacion de la valiables glovales.
inline void init(void)
{
    Figuras.index=NULL;
    Figuras.Plist=NULL;
    Figuras.numero=0;
    select_f=TYPELINEA;
    SelectColor=ZAFIRO;
    STIPPLE=0;
    Grosor=1;
    Nx=0xFFFF;
    Ax=0xF;
    Bx=0XF;
    Cx=0XF;
    Dx=0XF;
    Px=ANCHO/(xmax-xmin),Py=ALTO/(ymax-ymin);
    glClearColor(PaletaColor[BLANCO][0],PaletaColor[BLANCO][1],PaletaColor[BLANCO][2],0);
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
    while(Figuras.Plist!=NULL)
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
    ALTO=h;
    ANCHO=w;
    //esclaOrtoX=(GLdouble)w/h;
    //Escalar Ortho2D a tamaño de la pantalla. en x y en y
    Px=w/(xmax-xmin),Py=h/(ymax-ymin);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //redimenion del Ortho2D dependido de el escalar.
    gluOrtho2D(xmin,xmax,ymin,ymax);
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
        Figuras.index->STIPPLE=STIPPLE;
        Figuras.index->Nx=Nx;
        Figuras.index->grosor=Grosor;
        Figuras.index->color=SelectColor;
    }
        
    if(Figuras.index->V==NULL)//Crea la lista de puntos si esta no existe.
    {
        Figuras.index->V=(PUNTO*)malloc(sizeof(PUNTO));
        Figuras.index->V->next=NULL;
        Figuras.index->V->X=x/Px+xmin;//*esclaOrtoX;//se convierte el pixel en cordenadas del Ortho2D;
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
        Figuras.index->V->next->X=x/Px+xmin;//*esclaOrtoX;
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
        aux->next->X=x/Px+xmin;//*esclaOrtoX;
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
        while(V!=NULL)// si es lista.
        {
            aux=V;
            free(aux);
            V=V->next;
        }
    }
}


//raton pasivo.
void Raton(int x1,int y1)
{
    sprintf(Coordenadas,"(%i,%i)",x1,y1);
    if(pushRaton==1)//si se esta creando una figura se pre-dibuja.
    {   //Conversion de cordenadas.
        m_x=x1/Px+xmin;//*esclaOrtoX;
        m_y=-y1/Py-ymin;
    }
    glutPostRedisplay( );
}

void RatonActivo(int x1,int y1)
{
    sprintf(Coordenadas,"(%i,%i)",x1,y1);
    if(pushRaton==1)//si se esta creando una figura se pre-dibuja.
    {   //Conversion de cordenadas.

        m_x=x1/Px+xmin;//*esclaOrtoX;
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
    predibujo->grosor=Grosor;
    predibujo->STIPPLE=Figuras.index->STIPPLE;
    //Dibuajdo de la figura.
    glLineWidth(predibujo->grosor);
    if(predibujo->STIPPLE) glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, predibujo->Nx);
    FiguraSelecionada[predibujo->type].Dibujar(predibujo);
    if(predibujo->STIPPLE)glDisable(GL_LINE_STIPPLE);
    //Liberacion del vector y figura.
    glLineWidth(1.0);
    free(predibujo);  
    free(Vector);
}

void Cambio()
{
    //Cambio de valores de la figura.
    if(Figuras.index==NULL)return;//si no existe termina.
    Figuras.index->STIPPLE=STIPPLE;
    Figuras.index->Nx=Nx;
    Figuras.index->color=SelectColor;
    Figuras.index->grosor=Grosor;
}

//Colisiones.
void Selection(int x,int y)
{
	//(Delta1*ANCHO*1.0)+((Delta2*Ancho)/2.0)
	
	float PPPANCHO=ANCHO/20.0;
	float PPPALTO=ALTO/20.0;
	//SELECCION DEL COLOR
    float Delta1=0.01,Delta2=0.0825,Aux=0.8;
	if((x>=Delta1*ANCHO)&&(x<=(Delta2*ANCHO)/2.0)&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=BLANCO;
	else if((x>=(Delta1*ANCHO)*(1.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(1.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=MARFIL;
	else if((x>=(Delta1*ANCHO)*(2.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(2.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=AMARILLO;
	else if((x>=(Delta1*ANCHO)*(3.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(3.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=MALVA;
	else if((x>=(Delta1*ANCHO)*(4.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(4.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=SALMON;
	else if((x>=(Delta1*ANCHO)*(5.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(5.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=NARANJA;
	else if((x>=(Delta1*ANCHO)*(6.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(6.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=VIOLETA;
	else if((x>=(Delta1*ANCHO)*(7.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(7.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=ROSA;
	else if((x>=(Delta1*ANCHO)*(8.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(8.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=ROJO;
	else if((x>=(Delta1*ANCHO)*(9.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(9.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=CYAN_BAJO;
	else if((x>=(Delta1*ANCHO)*(10.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(10.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=VERDE_AGUA;
	else if((x>=(Delta1*ANCHO)*(11.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(11.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=CHARTREUSE;
	else if((x>=(Delta1*ANCHO)*(12.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(12.0+Aux))&&(y>=Delta1*ALTO)&&(y<=(Delta2*ALTO)/2.0))
		SelectColor=CELESTE;
//Segunda Linea de Colores.
	else if((x>=Delta1*ANCHO)&&(x<=(Delta2*ANCHO)/2.0)&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=GRIS;
	else if((x>=(Delta1*ANCHO)*(1.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(1.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=LIMA;
	else if((x>=(Delta1*ANCHO)*(2.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(2.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=MORADO;
	else if((x>=(Delta1*ANCHO)*(3.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(3.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=FUCSIA;
	else if((x>=(Delta1*ANCHO)*(4.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(4.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=ROJO_OSCURO;
	else if((x>=(Delta1*ANCHO)*(5.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(5.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=CYAN;
	else if((x>=(Delta1*ANCHO)*(6.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(6.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=VERDE_BAJO;
	else if((x>=(Delta1*ANCHO)*(7.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(7.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=VERDE;
	else if((x>=(Delta1*ANCHO)*(8.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(8.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=AZUL_CLARO;
	else if((x>=(Delta1*ANCHO)*(9.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(9.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=TRUQUESA;
	else if((x>=(Delta1*ANCHO)*(10.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(10.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=VERDE_KELLY;
	else if((x>=(Delta1*ANCHO)*(11.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(11.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=AZUL;
	else if((x>=(Delta1*ANCHO)*(12.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(12.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=ZAFIRO;
	else if((x>=(Delta1*ANCHO)*(13.0+Aux))&&(x<=((Delta2*ANCHO)/2.0)*(13.0+Aux))&&(y>=((Delta1+Delta2)*ALTO)/2.0)&&(y<=(Delta2*ALTO)))
		SelectColor=NEGRO;
	//Empiezan los botones de las figuras.
	else if((x>=(-9.3+10.0)*PPPANCHO)&&(x<=(-7.4+10.0)*PPPANCHO)&&(y>=((-1)*(7.9-10))*PPPALTO)&&(y<=(-1)*(6-10)*PPPALTO)){
        select_f=TYPELINEA;
	SelectedForm=0;
	}else if((x>=(-5.97+10.0)*PPPANCHO)&&(x<=(-4.07+10.0)*PPPANCHO)&&(y>=((-1)*(7.9-10))*PPPALTO)&&(y<=(-1)*(6-10)*PPPALTO)){
        select_f=TYPECUADRADO;
	SelectedForm=1;
	}else if((x>=(-2.64+10.0)*PPPANCHO)&&(x<=(-0.74+10.0)*PPPANCHO)&&(y>=((-1)*(7.9-10))*PPPALTO)&&(y<=(-1)*(6-10)*PPPALTO)){
		//Asignar Figura Rectangulo
		SelectedForm=2;
		select_f=TYPERECTAGULO;
	}else if((x>=(0.69+10.0)*PPPANCHO)&&(x<=(2.59+10.0)*PPPANCHO)&&(y>=((-1)*(7.9-10))*PPPALTO)&&(y<=(-1)*(6-10)*PPPALTO)){
		SelectedForm=3;
		//Asignar Figura POLIGONO
		select_f=TYPEPOLIGONOI;
	}else if((x>=(4.024+10.0)*PPPANCHO)&&(x<=(5.92+10.0)*PPPANCHO)&&(y>=((-1)*(7.9-10))*PPPALTO)&&(y<=(-1)*(6-10)*PPPALTO)){
		SelectedForm=4;
		//Asignar Figura CIRCULO
		select_f=TYPECIRCULO;
	}else if((x>=(7.35+10.0)*PPPANCHO)&&(x<=(9.25+10.0)*PPPANCHO)&&(y>=((-1)*(7.9-10))*PPPALTO)&&(y<=(-1)*(6-10)*PPPALTO)){
		SelectedForm=5;
		//Asignar Figura ELIPSE
		select_f=TYPEELIPSE;
	}
	Cambio();
}

void DrawInterface()
{
	glColor3f(0.8,0.8,0.8);//Se crea en rectangulo que contiene la interfaz
	glRectf(-10,10,10.0,5.95);
	RECTANGULO RecInter;
	RecInter.X=-9.99;
	RecInter.Y=9.99;
	RecInter.ancho=19.95;
	RecInter.alto=4;
	AsignaColor(BLANCO);
	rectangulo_(&RecInter);
	int i;
	float x=-9.9,y=9.9,Delta=0.8;
	CUADRADO CuadColor[27];
	for(i=0;i<13;i++)
	{
		//Primera Linea de Colores.
		AsignaColor(BLANCO-i);//Se crea el rectangulo que muestra el color
		glRectf(x+(i*(Delta)),y,x+(i*(Delta))+0.75,y-0.75);
		CuadColor[i].X=x+(i*(Delta)); //Se crea el rectangulo blanco que muestra el color.
		CuadColor[i].Y=y;
		CuadColor[i].Lado=0.75;
		AsignaColor(BLANCO);
		cuadrado_(&CuadColor[i]);
		
		//Segunda Linea de Colores.
		AsignaColor(BLANCO-(13+i));
		glRectf(x+(i*(Delta)),y-0.85,x+(i*(Delta))+0.75,y-1.6);
		CuadColor[14+i].X=x+(i*(Delta));
		CuadColor[14+i].Y=y-0.85;
		CuadColor[14+i].Lado=0.75;
		AsignaColor(BLANCO);
		cuadrado_(&CuadColor[(14+i)]);
		//glRectf(x+(i*(Delta)),y,i*(Delta)+0.75,y-0.75);
		
	}
	
	AsignaColor(BLANCO-(13+i));
	glRectf(x+(i*(Delta)),y-0.85,x+(i*(Delta))+0.75,y-1.6);
	CuadColor[26].X=x+(i*(Delta));
	CuadColor[26].Y=y-0.85;
	CuadColor[26].Lado=0.75;
	AsignaColor(BLANCO);
	cuadrado_(&CuadColor[(26)]);
	Delta=3.33;
	y=7.9;
	x=-9.3;
	CUADRADO CuadForm[6];
	AsignaColor(BLANCO);
	DibujarTexto("Selected Color : ",2.8,9.35);
	AsignaColor(SelectColor);
	glRectf(3.0,9.25,3.75,8.5);
	for(i=0;i<6;i++)
	{
		if(select_f==i)
            AsignaColor(VERDE);
        else
		    AsignaColor(NEGRO);
		//Se crean los botones
		CuadForm[i].X=x+(i*(Delta));
		CuadForm[i].Y=y;
		CuadForm[i].Lado=1.9;
		//AsignaColor(BLANCO);
		cuadrado_(&CuadForm[i]);
		LINEA line;
		CUADRADO cuad;
        RECTANGULO rec;
        POLIGONO poli;
        poli.NLados=4;
        PUNTOS Vector[4],centroP;
        poli.V=Vector;
		CIRCULO cir;
		ELIPSE eli;
		//Se crean las figuras.
		switch(i)
		{
			case 0:
					line.Xi= x+(i*(Delta)) + 0.4;
					line.Yi= y -0.4;
					line.Xf= x+(i*(Delta)) - 0.4 +1.9;
					line.Yf=  y  -1.6;
					//glPointSize(10.0);
					linea_(&line);
				break;
			case 1:
					cuad.X=x+(i*(Delta)) + 0.4;
					cuad.Y=y -0.4;
					cuad.Lado= 1.1;
					cuadrado_(&cuad);
				break;

			case 2:
					rec.X=x+(i*(Delta)) + 0.4;
					rec.Y= y -0.6;
					rec.ancho=1.1;
					rec.alto=0.8;
					rectangulo_(&rec);
				break;
            case 3:
                    centroP.X=x+(i*(Delta)) + 0.2;
                    centroP.Y= y -2;
                    poli.V[0].X=centroP.X+0;
                    poli.V[0].Y=centroP.Y+1;
                    poli.V[1].X=centroP.X+0.5;
                    poli.V[1].Y=centroP.Y+1.5;
                    poli.V[2].X=centroP.X+1;
                    poli.V[2].Y=centroP.Y+1.5;
                    poli.V[3].X=centroP.X+1.5;
                    poli.V[3].Y=centroP.Y+1;
                    poligonoi_(&poli);
				break;
			case 4:
					//glRectf(x+(i*(Delta)) + 0.95,9.9,x+(i*(Delta)) + 1.8,9.9-0.86);
					
					cir.x0=x+(i*(Delta)) + 0.95;
					cir.y0=y-0.95;
					cir.r=0.5;
					circulo_(&cir);
				break;
			case 5:
					eli.x0=x+(i*(Delta)) + 0.95;
					eli.y0=cir.y0=y-0.95;
					eli.r=0.5;
					eli.a=0.5;
					eli.b=0.3;
					eli.th=0.1;
					elipse_(&eli);
				break;
			default:
				break;
		}
    }
    DibujarTexto("Tipo de linea :",6,9.35);
    DibujarTexto("Grosor :",6,9);
    DibujarTexto(TipoLinea,8,9.35);
    DibujarSelect();
    DibujarTexto(Coordenadas,6,-9.9);	
}

void DibujarSelect()
{
    AsignaColor(SelectColor);		//COLOR
    if(STIPPLE)glEnable(GL_LINE_STIPPLE); // HABILITAMOS LA PROPIEDAD STIPPLE
    glLineWidth(Grosor);// ANCHO LINEA
	glLineStipple(3,Nx); // Dash Line ( pixeles por linea, patron linea punteada (HEXADECIMAL))
	glBegin(GL_LINES);
	glVertex2f(7.5,9.1);
    glVertex2f(9.5,9.1);
    glEnd();
    glLineWidth(1.0);
    if(STIPPLE)glDisable(GL_LINE_STIPPLE);// DESHABILITAMOS LA PROPIEDAD STIPPLE
}

void linea_(LINEA *l){
    glBegin(GL_LINES);
    glVertex2f(l->Xi,l->Yi);
    glVertex2f(l->Xf,l->Yf);
    glEnd();
}



void cuadrado_(CUADRADO *C)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(C->X,C->Y);
    glVertex2f(C->X+C->Lado,C->Y);
    glVertex2f(C->X+C->Lado,C->Y-C->Lado);
    glVertex2f(C->X,C->Y-C->Lado);
    glEnd();
}


void rectangulo_(RECTANGULO *R)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(R->X,R->Y);
    glVertex2f(R->X+R->ancho,R->Y);
    glVertex2f(R->X+R->ancho,R->Y-R->alto);
    glVertex2f(R->X,R->Y-R->alto);
    glEnd();
}

void poligonoi_(POLIGONO *P)
{
    unsigned char i;
    glBegin(GL_LINE_LOOP);
    for(i=0;i<P->NLados;i++)
    {
        glVertex2f(P->V[i].X,P->V[i].Y);
    }
    glEnd();
}

void circulo_(CIRCULO *C){
    GLdouble th=0,x,y,th_r=3.1415/180;
    glBegin(GL_LINE_LOOP);
    for(th=0;th<360;th+=1){
        x=C->r*cos(th*th_r)+C->x0;
        y=C->r*sin(th*th_r)+C->y0;
        glVertex2f(x,y);
    }
    glEnd();
}

void elipse_(ELIPSE *E){
    GLdouble th=0,x,y,x1,y1,th_r=3.1415/180;
    glBegin(GL_LINE_LOOP);
    for(th=0;th<360;th+=1){
        x=E->a*cos(th*th_r);
        y=E->b*sin(th*th_r);
        x1=x*cos(E->th*th_r)-sin(E->th*th_r)*y+E->x0;
        y1=x*sin(E->th*th_r)+cos(E->th*th_r)*y+E->y0;
        glVertex2f(x1,y1);
    }
    glEnd();
}

