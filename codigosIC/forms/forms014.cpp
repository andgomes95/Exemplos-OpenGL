
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
void kochcurve(int number, float x1, float y1, float x2, float y2){
    if(number > 0){
        float medx,medy,v1x,v1y,v2x,v2y,v3x,v3y,v4x,v4y,v5x,v5y,auxx,auxy;
        medx = (x1+x2)/2.0;
        medy = (y1+y2)/2.0;
        
        v1x = (x1+medx)/2.0;
        v1x = (v1x+medx)/2.0;
        v1y = (y1+medy)/2.0;
        v1y = (v1y+medy)/2.0;
        kochcurve(number-1,x1,y1,v1x,v1y);

        v2x = (x1+medx)/2.0;
        v2x = (v2x+medx)/2.0;
        v2y = (y2+medy)/2.0;
        v2y = (v2y+medy)/2.0;
        auxx = x1;
        auxy = y2;
        kochcurve(number-1,auxx,auxy,v2x,v2y);

        v3x = (x2+medx)/2.0;
        v3x = (v3x+medx)/2.0;
        v3y = (y2+medy)/2.0;
        v3y = (v3y+medy)/2.0;
        auxx = x2;
        auxy = y2;
        kochcurve(number-1,auxx,auxy,v3x,v3y);

        v4x = (x2+medx)/2.0;
        v4x = (v4x+medx)/2.0;
        v4y = (y1+medy)/2.0;
        v4y = (v4y+medy)/2.0;
        auxx = x2;
        auxy = y1;
        kochcurve(number-1,auxx,auxy,v4x,v4y);

        v5x = v1x;
        v5y = v1y;
        auxx = v3x;
        auxy = v3y;
        kochcurve(number-1,auxx,auxy,v5x,v5y);
        
        return;
    }else{
        glBegin(GL_LINE_STRIP);
        glVertex2d(x1,y1);
        glVertex2d(x1,y2);
        glVertex2d(x2,y2);
        glVertex2d(x2,y1);
        glVertex2d(x1,y1);
        glEnd();
        return;
    }
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    float x1,y1,x2,y2;
    x1 = 0.75f;
    y1 = 0.75f;
    x2 = -0.75f;
    y2 = -0.75f;
    glLoadIdentity();
    kochcurve(2,x1,y1,x2,y2);
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
   // glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
