
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
int window;

typedef struct point{
    float x;
    float y;
}pnt;
pnt verticeInicial,verticeFinal;

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

float calculaAngulo(pnt v1,pnt v2){
    pnt vetor,unit;
    unit.x = 1.0f;
    unit.y = 0.0f;
    float modulo,produtoEscalar;
    vetor.x = v2.x - v1.x;
    vetor.y = v2.y - v1.y;
    modulo = sqrt(pow(vetor.x,2)+pow(vetor.y,2));
    produtoEscalar = vetor.x*unit.x+vetor.y*unit.y;
    produtoEscalar = produtoEscalar/modulo;
    return produtoEscalar;
}

void koch(int number, pnt inicialVertice, pnt finalVertice){
    if(number == 0){
        glBegin(GL_LINES);
        glVertex2d(inicialVertice.x,inicialVertice.y);
        glVertex2d(finalVertice.x,finalVertice.y);
        glEnd();
    }else if(number >= 1){
        pnt vMed,v1,v2;
        float dist = 0.0,value;

        vMed.x = (inicialVertice.x+finalVertice.x)/2.0;
        vMed.y = (inicialVertice.y+finalVertice.y)/2.0;

        v1.x = (inicialVertice.x+vMed.x)/2.0;
        v1.y = (inicialVertice.y+vMed.y)/2.0;
        v1.x = (v1.x+vMed.x)/2.0;
        v1.y = (v1.y+vMed.y)/2.0;
        
        v2.x = (finalVertice.x+vMed.x)/2.0;
        v2.y = (finalVertice.y+vMed.y)/2.0;
        v2.x = (v2.x+vMed.x)/2.0;
        v2.y = (v2.y+vMed.y)/2.0;
    
        dist = sqrt(pow(inicialVertice.x-v1.x,2)+pow(inicialVertice.y-v1.y,2));
        vMed.y =vMed.y+ dist* (calculaAngulo(inicialVertice,finalVertice));
        if(inicialVertice.y>finalVertice.y)
            vMed.x =vMed.x+ dist*(1-calculaAngulo(inicialVertice,finalVertice));
        else vMed.x =vMed.x- dist*(1-calculaAngulo(inicialVertice,finalVertice));
        

        
        
        koch(number-1,inicialVertice,v1);
        koch(number-1,v1,vMed);
        koch(number-1,vMed,v2);
        koch(number-1,v2,finalVertice);
    }
    return;
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    verticeInicial.x = -0.95;
    verticeInicial.y = -1.0;
    verticeFinal.x = 0.95;
    verticeFinal.y = -1.0;
    koch(5,verticeInicial,verticeFinal);
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
    glPolygonMode(GL_FRONT, GL_LINE);
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
