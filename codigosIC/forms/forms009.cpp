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
#define FATIAS 15
using namespace std; 
int window,xMouse,yMouse;
typedef struct point{
    float x;
    float y;
}pnt;

vector<vector<pnt>> objetos;
vector<pnt> pincel; 

bool press = false;
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
void movementMouse(int x, int y){
    if (press == true && (xMouse != x || yMouse != y)){
        xMouse = x;
        yMouse = y;
        draw();
    }
}
void onMouseClick2(int button, int state, int x, int y){
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        xMouse = x;
        yMouse = y;
        press = true;
        draw();
        printf("press esquerda\n");
    }if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        press = false;
        objetos.push_back(pincel);
        pincel.clear();
        printf("solta esquerda %i, %i\n",x,y);
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

void draw(){
    pnt pixel;
    pixel.x = ((float)xMouse-(float)WIDTH/2.0)/(float)WIDTH*2.0;
    pixel.y = ((float)yMouse-(float)WIDTH/2.0)/(float)WIDTH*2.0;
    pincel.push_back(pixel);
}
void mandala(){
    
    float angule,r;
    for(auto j = objetos.begin(); j!= objetos.end();++j){
        glColor3f(rand()%10/10.0,rand()%10/10.0,rand()%10/10.0);
        for(int k=0;k<FATIAS;k++){
        glBegin(GL_LINE_STRIP);
        
            for (auto i = (*j).begin(); i!= (*j).end();++i){
                r = sqrt(pow(i->x,2)+pow(i->y,2));        
                angule = atan2(i->x,i->y);
                angule = angule *180.0/3.1415;
                angule = (float)k*360.0/FATIAS+angule;
                angule = angule/180.0*3.1415;
                glVertex2d(r*cos(angule),r*sin(angule));
            }
            glEnd();
        }
    }
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,0.0,0.0);
    for (auto i = pincel.begin(); i!= pincel.end();++i){
        glVertex2d(i->x,-i->y);
    }
    glEnd();
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if(press){
        draw();
    }
    mandala();
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
    glutMotionFunc(movementMouse);
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
