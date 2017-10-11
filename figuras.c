/*Hecho por Dezcorjm*/
#include "figuras.h"
//Identificador de color.
GLfloat xpos=0, zpos=0,next=0;
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
//Variables Globles
FIGURAS Figuras;
COLOR color;
DIBUJADO FiguraSelecionada[6];
GLfloat xmin=-10,xmax=10,ymin=-10,ymax=10;
GLfloat Px,Py;
TYPO_FIGURA select_f;
GLint Ax,Bx,Cx,Dx,Nx;
char STIPPLE=0;
void display()
{
  glClear (GL_COLOR_BUFFER_BIT);//Seleccionar buffer a limpear
  glClearColor(PaletaColor[NEGRO][0],PaletaColor[NEGRO][1],PaletaColor[NEGRO][2],0); //Color de la Ventana
  dibujarFiguras();//Dibujar Figuras
  //color seleccionado
  DibujarSelect();
glFlush();
}

void dibujarFiguras()
{
  if(Figuras.Plist==NULL)
    return;
  LISTA *star;
  star=Figuras.Plist;
  //glBegin(GL_LINE_STRIP);
  while(star!=NULL)
  {
    glLineWidth(1.0);
    if(star->STIPPLE) glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,star->Nx);
    FiguraSelecionada[star->type].Dibujar(star);
    if(star->STIPPLE)glDisable(GL_LINE_STIPPLE); // DESHABILITAMOS LA PROPIEDAD STIPPLE
    star=star->next;
  }
}

void linea(LISTA* list)
{
    AsignaColor(list->color);
    glBegin(GL_LINES);
    glVertex2f(list->V[0].X/Px+xmin,list->V[0].Y/Py-ymin);
    glVertex2f(list->V[1].X/Px+xmin,list->V[1].Y/Py-ymin);
    glEnd();
}

void cuadrado(LISTA* list)
{
    AsignaColor(list->color);
    GLdouble th=0,x,y,x1,y1,r,th_r=3.1415/180;
    x=(list->V[0].X-list->V[1].X)/2;
    y=(list->V[0].Y-list->V[1].Y)/2;
    x1=(list->V[0].X+list->V[1].X)/2;
    y1=(list->V[0].Y+list->V[1].Y)/2;
    r=sqrt(x*x+y*y);
    glBegin(GL_LINE_LOOP);
    for(th=-45;th<405;th+=90)
    {
        x=r*cos(th*th_r)+x1;
        y=r*sin(th*th_r)+y1;
        glVertex2f(x/Px+xmin,y/Py-ymin);
    }
    glEnd();
}

void rectangulo(LISTA* list)
{
    AsignaColor(list->color);
    glBegin(GL_LINE_LOOP);
    glVertex2f(list->V[0].X/Px+xmin,list->V[0].Y/Py-ymin);
    glVertex2f(list->V[0].X/Px+xmin,list->V[1].Y/Py-ymin);
    glVertex2f(list->V[1].X/Px+xmin,list->V[1].Y/Py-ymin);
    glVertex2f(list->V[1].X/Px+xmin,list->V[0].Y/Py-ymin);
    glEnd();
}

void poligonoi(LISTA* list)
{
    int i=0;
    AsignaColor(list->color);
    glBegin(GL_LINE_LOOP);
    for(i=0;i<list->Nv;i++)
        {
        glVertex2f(list->V[i].X/Px+xmin,list->V[i].Y/Py-ymin);
        }
    glEnd();
}

void circulo(LISTA* list)
{
    AsignaColor(list->color);
    GLdouble th=0,x,y,x1,y1,r,th_r=3.1415/180;
    x=(list->V[0].X-list->V[1].X)/2;
    y=(list->V[0].Y-list->V[1].Y)/2;
    x1=(list->V[0].X+list->V[1].X)/2;
    y1=(list->V[0].Y+list->V[1].Y)/2;
    r=sqrt(x*x+y*y);
    glBegin(GL_LINE_LOOP);
    for(th=0;th<360;th+=1)
    {
        x=r*cos(th*th_r)+x1;
        y=r*sin(th*th_r)+y1;
        glVertex2f(x/Px+xmin,y/Py-ymin);
    }
    glEnd();
}

void elipse(LISTA* list)
{
    AsignaColor(list->color);
    GLdouble th=0,x,y,x1,y1,a,b,th_r=3.1415/180;
    a=fabs(list->V[0].X-list->V[1].X)/2;
    b=fabs(list->V[0].Y-list->V[1].Y)/2;
    x1=(list->V[0].X+list->V[1].X)/2;
    y1=(list->V[0].Y+list->V[1].Y)/2;
    glBegin(GL_LINE_LOOP);
    for(th=0;th<360;th+=1){
        x=a*cos(th*th_r)+x1;
        y=b*sin(th*th_r)+y1;
        glVertex2f(x/Px+xmin,y/Py-ymin);
    }
    glEnd();
}

void AsignaColor(COLOR color)
{
    glColor3f(PaletaColor[color][0],PaletaColor[color][1],PaletaColor[color][2]);
}


void ControlRaton( int button, int state, int x, int y )
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        setlistP(x,y);
        if ((Figuras.index->type!=TYPEPOLIGONOI)&&Figuras.index->Nv==2)
        {
            Figuras.index->color=color;
            Figuras.index->STIPPLE=STIPPLE;
            setlist(Figuras.index);
        }

        glutPostRedisplay();
    }
    if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {

        if(Figuras.index!=NULL)
        if ((Figuras.index->type==TYPEPOLIGONOI))
        {
            setlistP(x,y);
            Figuras.index->color=color;
            Figuras.index->STIPPLE=STIPPLE;
            setlist(Figuras.index);
        }
        glutPostRedisplay();
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
    glutPostRedisplay( );
}

void init(void)
{
    Figuras.index=NULL;
    Figuras.Plist=NULL;
    select_f=TYPELINEA;
    color=ZAFIRO;
    STIPPLE=0;
    Nx=0xFFFF;
    Ax=0xF;
    Bx=0XF;
    Cx=0XF;
    Dx=0XF;
    Px=ANCHO/(xmax-xmin),Py=ALTO/(ymax-ymin);
    FiguraSelecionada[TYPELINEA].Dibujar=linea;
    FiguraSelecionada[TYPECUADRADO].Dibujar=cuadrado;
    FiguraSelecionada[TYPERECTAGULO].Dibujar=rectangulo;
    FiguraSelecionada[TYPEPOLIGONOI].Dibujar=poligonoi;
    FiguraSelecionada[TYPECIRCULO].Dibujar=circulo;
    FiguraSelecionada[TYPEELIPSE].Dibujar=elipse;
}

void cierre()
{
  printf("Cierre\n");
  if(Figuras.index!=NULL)
  {
      liberar(Figuras.index->V);
      free(Figuras.index);
  }
  if(Figuras.Plist==NULL)return;
  LISTA *aux;
  while(Figuras.Plist->next!=NULL){
    free(Figuras.Plist->V);
    aux=Figuras.Plist;
    Figuras.Plist=Figuras.Plist->next;
    free(aux);
  }
}


void setlist(LISTA* list)
{
    int i=0;
  if(Figuras.Plist==NULL)
  {
    Figuras.Plist=list;
    Figuras.Plist->next=NULL;
    PUNTO *aux,*Vector;
    aux=list->V;
    Vector=(PUNTO*)malloc(sizeof(PUNTO)*list->Nv);
    for(i=0;i<list->Nv;i++)
    {
        Vector[i].X=aux->X;
        Vector[i].Y=aux->Y;
        Vector[i].next=NULL;
        aux=aux->next;
    }
    liberar(Figuras.Plist->V);
    Figuras.Plist->V=Vector;
    Figuras.index=NULL;
    return;
  }
  else
  {
    LISTA *aux;
    aux=Figuras.Plist;
    while(aux->next!=NULL)
    {
      aux=aux->next;
    }

    aux->next=list;
    aux->next->next=NULL;
    PUNTO *aux1,*Vector;
    aux1=list->V;
    Vector=(PUNTO*)malloc(sizeof(PUNTO)*list->Nv);
    for(i=0;i<list->Nv;i++)
    {
        Vector[i].X=aux1->X;
        Vector[i].Y=aux1->Y;
        Vector[i].next=NULL;
        aux1=aux1->next;
    }
    liberar(aux->next->V);
    aux->next->V=Vector;
    Figuras.index=NULL;

  }

  //while(Figuras.Plist->back!=NULL){
  //  Figuras.Plist=Figuras.Plist->back;
  //}
}

void displayView(GLsizei w,GLsizei h)
{
  glViewport(0,0,w,h);
  Px=w/(xmax-xmin),Py=h/(ymax-ymin);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xmin,xmax,ymin,ymax);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void setlistP(GLint x, GLint y)
{
    if(Figuras.index==NULL)
    {
        Figuras.index=(LISTA*)malloc(sizeof(LISTA));
        Figuras.index->V=NULL;
        Figuras.index->type=select_f;
        Figuras.index->Nv=0;
        Figuras.index->STIPPLE=0;
        Figuras.index->Nx=Nx;
        Figuras.index->color=color;
    }

    if(Figuras.index->V==NULL)
    {
        Figuras.index->V=(PUNTO*)malloc(sizeof(PUNTO));
        Figuras.index->V->next=NULL;
        Figuras.index->V->X=x;
        Figuras.index->V->Y=-y;
        Figuras.index->Nv++;
    }
    else if( Figuras.index->V->next==NULL)
    {
        Figuras.index->V->next=(PUNTO*)malloc(sizeof(PUNTO));
        Figuras.index->V->next->next=NULL;
        Figuras.index->V->next->X=x;
        Figuras.index->V->next->Y=-y;
        Figuras.index->Nv++;
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
        aux->next->X=x;
        aux->next->Y=-y;
        Figuras.index->Nv++;
    }
}
void liberar(PUNTO *V)
{
    if(V==NULL)return;
    if(V->next==NULL)
    {
        free(V);
    }
    else
    {
        PUNTO *aux;
        while(V->next!=NULL)
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
