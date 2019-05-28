
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
void mengersponge(int number, float size,float initx,float inity,float initz){
    float move;
    move = size/3.0;
    if(number > 1){
        mengersponge(number-1,size/3.0,initx+move,inity+move,initz);
        mengersponge(number-1,size/3.0,initx+move,inity,initz+move);
        mengersponge(number-1,size/3.0,initx+move,inity+move,initz+move);
        mengersponge(number-1,size/3.0,initx+move,inity-move,initz);
        mengersponge(number-1,size/3.0,initx+move,inity,initz-move);
        mengersponge(number-1,size/3.0,initx+move,inity-move,initz-move);
        mengersponge(number-1,size/3.0,initx+move,inity-move,initz+move);
        mengersponge(number-1,size/3.0,initx+move,inity+move,initz-move);

        mengersponge(number-1,size/3.0,initx-move,inity+move,initz);
        mengersponge(number-1,size/3.0,initx-move,inity,initz+move);
        mengersponge(number-1,size/3.0,initx-move,inity+move,initz+move);
        mengersponge(number-1,size/3.0,initx-move,inity-move,initz);
        mengersponge(number-1,size/3.0,initx-move,inity,initz-move);
        mengersponge(number-1,size/3.0,initx-move,inity-move,initz-move);
        mengersponge(number-1,size/3.0,initx-move,inity-move,initz+move);
        mengersponge(number-1,size/3.0,initx-move,inity+move,initz-move);

        mengersponge(number-1,size/3.0,initx,inity+move,initz+move);
        mengersponge(number-1,size/3.0,initx,inity-move,initz-move);
        mengersponge(number-1,size/3.0,initx,inity+move,initz-move);
        mengersponge(number-1,size/3.0,initx,inity-move,initz+move);
        return;
    }else{
        glPushMatrix();
        glTranslatef(initx,inity,initz);
        glutSolidCube(size);
        glPopMatrix();
        return;
    }
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    ///glRotatef(45,1.0,1.0,0.0);

    GLfloat luzAmbiente[4]={1.0,1.0,1.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente); 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzAmbiente); 
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    mengersponge(3,0.5,0.0,0.0,0.0);

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
    return 0;
}
