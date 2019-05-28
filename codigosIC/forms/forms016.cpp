
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
void sierpinskicarpet(int number, float x1, float y1, float x2,float y2){
    float lenX,lenY;
    lenX = x1-x2;
    lenY = y1-y2;
    glBegin(GL_QUADS);
    glVertex2d(x1-lenX/3.0,y1-lenY/3.0);
    glVertex2d(x1-lenX/3.0,y2+lenY/3.0);
    glVertex2d(x2+lenX/3.0,y2+lenY/3.0);
    glVertex2d(x2+lenX/3.0,y1-lenY/3.0);
    glEnd();
    if(number > 1){
        //float x12,y12,x23,y23,x13,y13;
        sierpinskicarpet(number-1,x1,y1,x1-lenX/3.0,y1-lenY/3.0);
        sierpinskicarpet(number-1,x1-lenX/3.0,y1,x2+lenX/3.0,y1-lenY/3.0);
        sierpinskicarpet(number-1,x2+lenX/3.0,y1,x2,y1-lenY/3.0);
        sierpinskicarpet(number-1,x2+lenX/3.0,y1-lenY/3.0,x2,y2+lenY/3.0);
        sierpinskicarpet(number-1,x2+lenX/3.0,y2+lenY/3.0,x2,y2);
        sierpinskicarpet(number-1,x1-lenX/3.0,y2+lenY/3.0,x2+lenX/3.0,y2);
        sierpinskicarpet(number-1,x1,y2+lenY/3.0,x1-lenX/3.0,y2);
        sierpinskicarpet(number-1,x1,y1-lenY/3.0,x1-lenX/3.0,y2+lenY/3.0);
        return;
    }else{
        return;
    }
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    float v1x,v1y,v2x,v2y;
    v1x = -1.0f;
    v1y = -1.0f;
    v2x = 1.0f;
    v2y = 1.0f;
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    sierpinskicarpet(3,v1x,v1y,v2x,v2y);
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
