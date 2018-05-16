
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>
#include <string.h>
#include <stdio.h>
GLfloat tamCircle,movX, movY,movX0,movY0,zRotated;
#include <math.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
GLint onMouse,type;
typedef struct type_object{
        float x;
        float y;
        int type;
        float tamCircle;
        float x0;
        float y0;
        type_object *next;
}t_obj;
t_obj *header, *actual,*last;
typedef struct mosaicgraph_window{
        float x;
        float y;
        float width;
        float height;
        float red;
        float green;
        float blue;
        float alpha;
        float fullscreen;
        char title[128];
        int id;
        void (*process)(void *self);
}mosaicgraph_window_t;
mosaicgraph_window_t * mosaicgraph_create_window(float width, float height,float x, float y){
    mosaicgraph_window_t * window = (mosaicgraph_window_t *) malloc(sizeof(mosaicgraph_window_t));
    window->fullscreen = 0;
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    return window;
}
int mosaicgraph_draw_window(mosaicgraph_window_t * window){
    glutInitWindowPosition(window->x, window->y);
    glutInitWindowSize(window->width, window->height);
    glClearColor(window->red, window->green, window->blue, window->alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    window->id = glutCreateWindow(window->title);
    if (window->fullscreen){
        glutFullScreen();
    }
    return window->id;
}
void mosaicgraph_draw_circle(float radius){
    /**/glBegin(GL_POLYGON);
        for (int i=0; i < 360; i++){
            float degInRad = i*3.14159/180;
            glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
        }
    glEnd();/*
    glutSolidSphere(radius,200,200);/**/
}
void mosaicgraph_draw_semicircle(float radius){
    /**/glBegin(GL_POLYGON);
        for (int i=0; i < 180; i++){
            float degInRad = i*3.14159/180;
            glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
        }
    glEnd();/*
    glutSolidSphere(radius,200,200);/**/
}

void display(){

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
  glLoadIdentity();
  actual = header;
  glColor3f(0.1f,0.8f,0.0);
  while(actual != NULL){
    if(actual->type == 1){
      glPushMatrix();
      glTranslatef(actual->x,actual->y,0.0);
      mosaicgraph_draw_circle(actual->tamCircle);
      glPopMatrix();
    }else if(actual->type == 2){
      glBegin(GL_LINES);
        glVertex3f(actual->x,actual->y,0.0);
        glVertex3f(actual->x0,actual->y0,0.0);
      glEnd();
    }else if(actual->type == 3){
      glBegin(GL_QUADS);
      glVertex3f(actual->x,actual->y,0.0);
      glVertex3f(actual->x,actual->y0,0.0);
      glVertex3f(actual->x0,actual->y0,0.0);
      glVertex3f(actual->x0,actual->y,0.0);
      glEnd();
    }else if(actual->type == 4){
      glPushMatrix();
      glTranslatef(actual->x,actual->y,0.0);
      mosaicgraph_draw_semicircle(actual->tamCircle);
      glPopMatrix();
    }
    actual = actual->next;
  }
  glColor3f(0.8f,0.2f,0.0);
  if(onMouse == 1 && type == 1){
    glTranslatef(movX,movY,0.0);
    glPushMatrix();
    mosaicgraph_draw_circle(tamCircle);
    glPopMatrix();
  }else if(onMouse == 1 && type == 2){
    glBegin(GL_LINES);
    glVertex3f(movX,movY,0.0);
    glVertex3f(movX0,movY0,0.0);
    glEnd();
  }else if(onMouse == 1 && type == 3){
    glBegin(GL_QUADS);
      glVertex3f(movX,movY,0.0);
      glVertex3f(movX,movY0,0.0);
      glVertex3f(movX0,movY0,0.0);
      glVertex3f(movX0,movY,0.0);
    glEnd();
  }else if(onMouse == 1 && type == 4){
    mosaicgraph_draw_semicircle(tamCircle);
  }
  glutSwapBuffers();
  glFlush();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){
      glutDestroyWindow(window);
      exit(0);
    }if (key == 97){
      type = 1;
    }if (key == 115){
      type = 2;
    }if (key == 100){
      type = 3;
    }if (key == 102){
      type = 4;
    }
}
t_obj * createObject(){
  t_obj *obj = (t_obj*)(malloc (sizeof(t_obj)));
  obj->x = movX;
  obj->y = movY;
  obj->x0 = movX0;
  obj->y0 = movY0;
  obj->type = type;
  obj->tamCircle = tamCircle;
  obj->next = NULL;
  return obj;
}
void mouseClicks(int button, int state, int x, int y) {
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      onMouse = 1;
  }else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    if(header == NULL){
      header = createObject();
      last = header;
    }else{
      last->next = createObject();
      last = last->next;
    }
    tamCircle = 0.0;
    onMouse = 0;
  }
}
void MouseAndandoNaoPressionado (int x, int y)
{
    movX = (((float)x-250.0)/250.0);
    movY = -1.0*(((float)y-250.0)/250.0);
    //printf("%f - %f\n",movX,movY);
}
void MouseAndandoPressionado (int x, int y)
{
    movX0 = (((float)x-250.0)/250.0);
    movY0 = -1.0*(((float)y-250.0)/250.0);
    //printf("Mouse ANDANDO pressionado na janela. Posição: (%d, %d)\n", x,y);
}
void idle(){
    if(onMouse ==1){
      tamCircle +=0.001;
    }
    display();
}
/*void reshapeFunc(int x, int y){
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);
}*/
int main (int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    mosaicgraph_window_t * window = mosaicgraph_create_window(500,500,0,0);
    strcpy(window->title, "Main Page");
    type = 1;
    mosaicgraph_draw_window(window);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glutDisplayFunc(display);
  //  glutReshapeFunc(reshapeFunc);

    glutIdleFunc(&idle);
    glutMouseFunc(mouseClicks);
    // movimento SEM botão pressionado
    glutPassiveMotionFunc(MouseAndandoNaoPressionado);

    // movimento COM botão pressionado
    glutMotionFunc(MouseAndandoPressionado);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
