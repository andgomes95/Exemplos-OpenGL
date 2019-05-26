
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
pnt v1,v2;

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
void sierpinski(int number, pnt vertice1, pnt vertice2){
    if(number > 0){
        pnt vMed,v1,v2,v3,v4,v5,vaux;
        vMed.x = (vertice1.x+vertice2.x)/2.0;
        vMed.y = (vertice1.y+vertice2.y)/2.0;
        
        v1.x = (vertice1.x+vMed.x)/2.0;
        v1.x = (v1.x+vMed.x)/2.0;
        v1.y = (vertice1.y+vMed.y)/2.0;
        v1.y = (v1.y+vMed.y)/2.0;
        sierpinski(number-1,vertice1,v1);

        v2.x = (vertice1.x+vMed.x)/2.0;
        v2.x = (v2.x+vMed.x)/2.0;
        v2.y = (vertice2.y+vMed.y)/2.0;
        v2.y = (v2.y+vMed.y)/2.0;
        vaux.x = vertice1.x;
        vaux.y = vertice2.y;
        sierpinski(number-1,vaux,v2);

        v3.x = (vertice2.x+vMed.x)/2.0;
        v3.x = (v3.x+vMed.x)/2.0;
        v3.y = (vertice2.y+vMed.y)/2.0;
        v3.y = (v3.y+vMed.y)/2.0;
        vaux.x = vertice2.x;
        vaux.y = vertice2.y;
        sierpinski(number-1,vaux,v3);

        v4.x = (vertice2.x+vMed.x)/2.0;
        v4.x = (v4.x+vMed.x)/2.0;
        v4.y = (vertice1.y+vMed.y)/2.0;
        v4.y = (v4.y+vMed.y)/2.0;
        vaux.x = vertice2.x;
        vaux.y = vertice1.y;
        sierpinski(number-1,vaux,v4);

        v5.x = v1.x;
        v5.y = v1.y;
        vaux.x = v3.x;
        vaux.y = v3.y;
        sierpinski(number-1,vaux,v5);
        
        return;
    }else{
        glBegin(GL_LINE_STRIP);
        glVertex2d(vertice1.x,vertice1.y);
        glVertex2d(vertice1.x,vertice2.y);
        glVertex2d(vertice2.x,vertice2.y);
        glVertex2d(vertice2.x,vertice1.y);
        glVertex2d(vertice1.x,vertice1.y);
        glEnd();
        return;
    }
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    v1.x = 0.75f;
    v1.y = 0.75f;
    v2.x = -0.75f;
    v2.y = -0.75f;
    glLoadIdentity();
    sierpinski(4,v1,v2);
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
