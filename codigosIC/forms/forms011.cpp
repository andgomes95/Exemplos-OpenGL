
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>
#define ESCAPE 27 //Valor em ASCII do ESC
#define WIDTH 500
#define HEIGHT 500
using namespace std; 
int window,xMouse,yMouse;
typedef struct point{
    float x;
    float y;
}pnt;

bool first = false;
bool second = false;
bool third = false;
pnt pontoInicial;
pnt pontoFinal;
pnt pontoCurva;
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
void draw();
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
void onMouseClick2(int button, int state, int x, int y){
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        if(first == false){
            first = true;
            pontoInicial.x = (x-(float)WIDTH/2.0)/(float)WIDTH*2.0;
            pontoInicial.y = -(y-(float)WIDTH/2.0)/(float)WIDTH*2.0;
        } else if(second == false){
            second = true;
            pontoFinal.x = (x-(float)WIDTH/2.0)/(float)WIDTH*2.0;
            pontoFinal.y = -(y-(float)WIDTH/2.0)/(float)WIDTH*2.0;
        }else{
            third = true;
            pontoCurva.x = (x-(float)WIDTH/2.0)/(float)WIDTH*2.0;
            pontoCurva.y = -(y-(float)WIDTH/2.0)/(float)WIDTH*2.0;
        }
        printf("press esquerda\n");
    }if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if(third == true){
            //desenha
        }
        printf("solta esquerda %f, %f\n",pontoInicial.x,pontoInicial.y);
        printf("solta esquerda %f, %f\n",pontoFinal.x,pontoFinal.y);
        
    }if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        printf("press meio\n");
    }if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
        printf("solta meio\n");
    }if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        printf("press direito\n");
    }if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        printf("solta direito\n");
    }
}

void bezier(){
    float ax,ay,bx,by,bezierX,bezierY;
    glColor3f(0.5f,0.5f,0.5f);
    glBegin(GL_LINES);
    glVertex2f(pontoInicial.x,pontoInicial.y);
    glVertex2f(pontoCurva.x,pontoCurva.y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(pontoCurva.x,pontoCurva.y);
    glVertex2f(pontoFinal.x,pontoFinal.y);
    glEnd();
    //Quadrado do ponto inicial
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(pontoInicial.x-0.01,pontoInicial.y+0.01);
    glVertex2f(pontoInicial.x-0.01,pontoInicial.y-0.01);
    glVertex2f(pontoInicial.x+0.01,pontoInicial.y-0.01);
    glVertex2f(pontoInicial.x+0.01,pontoInicial.y+0.01);
    glEnd();
    //Quadrado centro linha inicial
    ax = (pontoInicial.x+pontoCurva.x)/2.0;
    ay = (pontoInicial.y+pontoCurva.y)/2.0;
    bx = (pontoCurva.x+pontoFinal.x)/2.0;
    by = (pontoCurva.y+pontoFinal.y)/2.0;
    bezierX = (ax+bx)/2.0;
    bezierY = (ay+by)/2.0;
    glBegin(GL_LINE_STRIP);
    for (int i =0;i<100;i++ ){
        ax = (pontoInicial.x*(float)i/50.0+pontoCurva.x*(100.0-(float)i)/50.0)/2.0;
        ay = (pontoInicial.y*(float)i/50.0+pontoCurva.y*(100.0-(float)i)/50.0)/2.0;
        bx = (pontoCurva.x*(float)i/50.0+pontoFinal.x*(100.0-(float)i)/50.0)/2.0;
        by = (pontoCurva.y*(float)i/50.0+pontoFinal.y*(100.0-(float)i)/50.0)/2.0;
        bezierX = (ax*(float)i/50.0+bx*(100.0-(float)i)/50.0)/2.0;
        bezierY = (ay*(float)i/50.0+by*(100.0-(float)i)/50.0)/2.0;
        glVertex2f(bezierX,bezierY);
    }
    glEnd();
}


void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    bezier();
    glutSwapBuffers();
}


void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }
    
}
void idle(){
    
    display();
}
int main (int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    mosaicgraph_window_t * window = mosaicgraph_create_window(WIDTH,HEIGHT,0,0);
    strcpy(window->title, "Main Page");
    mosaicgraph_draw_window(window);   
    glutMouseFunc(onMouseClick2);
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
