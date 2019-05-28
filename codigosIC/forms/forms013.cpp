
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
void kochcurve(int number,float x1, float y1, float x2, float y2){
    float distx = x2-x1,disty = y2-y1;
    float xm1 = x1+distx/3.0;
    float xm2 = x1+2.0*distx/3.0;
    float xm = x1+distx/2.0;
    float ym1 = y1+disty/3.0;
    float ym2 = y1+2.0*disty/3.0;
    float ym = y1+disty/2.0;
    float pontoAltox,pontoAltoy;
    float modulo = sqrt(pow(distx,2)+pow(disty,2));
    float xvec = distx/modulo;
    float yvec = disty/modulo;
    pontoAltoy = (modulo*xvec*sqrt(3.0))/(6.0);
    pontoAltox = -(pontoAltoy*yvec)/xvec;
    modulo = sqrt(pow(pontoAltox,2)+pow(pontoAltoy,2));
    pontoAltoy = ym+pontoAltoy;
    pontoAltox = xm+pontoAltox;
    if(number > 1){
        kochcurve(number-1,x1,y1,xm1,ym1);
        kochcurve(number-1,xm1,ym1,pontoAltox,pontoAltoy);
        kochcurve(number-1,pontoAltox,pontoAltoy,xm2,ym2);
        kochcurve(number-1,xm2,ym2,x2,y2);
        return;
    }else{
        glBegin(GL_LINE_STRIP);
        glVertex2d(x1,y1);
        glVertex2d(xm1,ym1);
        glVertex2d(pontoAltox,pontoAltoy);//mudar
        glVertex2d(xm2,ym2);
        glVertex2d(x2,y2);
        glEnd();
        return;
    }
}
void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    float x1=-1.0,y1=-0.90,x2=1.0,y2=-0.90;
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    kochcurve(8,x1,y1,x2,y2);
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
