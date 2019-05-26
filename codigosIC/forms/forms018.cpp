
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
void peanox(int number, float x1, float x2,float y);
void peanoy(int number, float y1, float y2,float x){
    float xm1,xm2,ym1,ym2;
    ym1 = y1+(y2-y1)/3.0;
    ym2 = y1+2.0*(y2-y1)/3.0;
    xm1 = x+(y2-y1)/3.0;
    xm2 = x-(y2-y1)/3.0;
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2d(x,y1);
    glVertex2d(x,y2);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(xm1,ym1);
    glVertex2d(xm1,ym2);
    glVertex2d(xm2,ym2);
    glVertex2d(xm2,ym1);
    glVertex2d(xm1,ym1);
    glEnd();
    glPopMatrix();
    if(number > 1){
        peanoy(number-1,y1,ym1,x);
        peanoy(number-1,ym1,ym2,x);
        peanoy(number-1,ym2,y2,x);
        peanoy(number-1,ym1,ym2,xm1);
        peanoy(number-1,ym1,ym2,xm2);
        peanox(number-1,xm1,x,ym1);
        peanox(number-1,x,xm2,ym1);
        peanox(number-1,xm1,x,ym2);
        peanox(number-1,x,xm2,ym2);
        return;
    }else{
        return;
    }
}
void peanox(int number, float x1, float x2,float y){
    float xm1,xm2,ym1,ym2;
    xm1 = x1+(x2-x1)/3.0;
    xm2 = x1+2.0*(x2-x1)/3.0;
    ym1 = y+(x2-x1)/3.0;
    ym2 = y-(x2-x1)/3.0;
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2d(x1,y);
    glVertex2d(x2,y);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(xm1,ym1);
    glVertex2d(xm1,ym2);
    glVertex2d(xm2,ym2);
    glVertex2d(xm2,ym1);
    glVertex2d(xm1,ym1);
    glEnd();
    glPopMatrix();
    if(number > 1){
        peanox(number-1,x1,xm1,y);
        peanox(number-1,xm1,xm2,y);
        peanox(number-1,xm2,x2,y);
        peanox(number-1,xm1,xm2,ym1);
        peanox(number-1,xm1,xm2,ym2);
        peanoy(number-1,ym1,y,xm1);
        peanoy(number-1,y,ym2,xm1);
        peanoy(number-1,ym1,y,xm2);
        peanoy(number-1,y,ym2,xm2);
        return;
    }else{
        return;
    }
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    float v1x,v2x,v1y,v2y;
    v1x = -0.9f;
    v2x = 0.9f;
    peanox(5,v1x,v2x,0.0);
    glLoadIdentity();
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
    glPolygonMode(GL_FRONT, GL_FILL);
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
    return 0;
}
