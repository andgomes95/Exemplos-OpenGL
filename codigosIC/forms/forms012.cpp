
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
pnt v1,v2,v3;

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
void sierpinski(int number, pnt vertice1, pnt vertice2, pnt vertice3){
    glBegin(GL_LINE_STRIP);
    glVertex2d(vertice1.x,vertice1.y);
    glVertex2d(vertice2.x,vertice2.y);
    glVertex2d(vertice3.x,vertice3.y);
    glEnd();
    if(number > 1){
        pnt v12,v23,v13;
        v12.x = (vertice1.x+vertice2.x)/2.0;
        v12.y = (vertice1.y+vertice2.y)/2.0;
        v13.x = (vertice1.x+vertice3.x)/2.0;
        v13.y = (vertice1.y+vertice3.y)/2.0;
        v23.x = (vertice2.x+vertice3.x)/2.0;
        v23.y = (vertice2.y+vertice3.y)/2.0;

        sierpinski(number-1,vertice1,v12,v13);
        sierpinski(number-1,vertice2,v12,v23);
        sierpinski(number-1,vertice3,v23,v13);
        return;
    }else{
        return;
    }
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    v1.x = 1.0f;
    v1.y = -1.0f;
    v2.x = 0.0f;
    v2.y = 1.0f;
    v3.x = -1.0f;
    v3.y = -1.0f;
    glLoadIdentity();
    sierpinski(12,v1,v2,v3);
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
