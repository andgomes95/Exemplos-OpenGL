
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream> // for cout
#include <math.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
float radius_1 = 0.5;
float * circle_1_color ;
using namespace std;
typedef struct points{
	float x;
	float y;
}pnt;

list<pnt> pontos;

void circle_radius_1(float value){
	radius_1 = value;
}

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

void mosaicgraph_draw_circle(pnt p,float * rgb){
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
        glVertex2f(p.x-0.05,p.y-0.05);
        glVertex2f(p.x+0.05,p.y-0.05);
        glVertex2f(p.x+0.05,p.y+0.05);
        glVertex2f(p.x-0.05,p.y+0.05);
	glEnd();
}

void voronoi(){
    float dis1,dis2,dis3,x0,y0;
    pnt p,q,r;
    p.x = 0.25;
    p.y = 0.75;
    q.x = 0.5;
    q.y = -0.5;
    r.x = -0.25;
    r.y = 0.5;
    pontos.push_back(p);
    pontos.push_back(q);
    pontos.push_back(r);

    for(int i =0;i<200;i++){
        for(int j=0;j<200;j++){
            x0 = (float)i/100.0-1.0;
            y0 = (float)j/100.0-1.0;
            dis1 = sqrt(pow((p.x-x0),2)+pow((p.y-y0),2));
            dis2 = sqrt(pow((q.x-x0),2)+pow((q.y-y0),2));
            dis3 = sqrt(pow((r.x-x0),2)+pow((r.y-y0),2));
            if(dis1<dis2){
                if(dis1<dis3){
                    glColor3f(1.0,0.0,0.0);
                    glBegin(GL_POINTS);
                        glVertex2f(x0,y0);
                    glEnd();
                }else{
                    glColor3f(0.0,0.0,1.0);
                    glBegin(GL_POINTS);
                        glVertex2f(x0,y0);
                    glEnd();
                }
            }else if(dis2<dis3){
                glColor3f(0.0,1.0,0.0);
                glBegin(GL_POINTS);
                    glVertex2f(x0,y0);
                glEnd();
            }else{
                if(dis1<dis3){
                    glColor3f(0.0,1.0,0.0);
                    glBegin(GL_POINTS);
                        glVertex2f(x0,y0);
                    glEnd();
                }else{
                    glColor3f(0.0,0.0,1.0);
                    glBegin(GL_POINTS);
                        glVertex2f(x0,y0);
                    glEnd();
                }
            }
        }
    }

}


void display(){

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
	glLoadIdentity();
    voronoi();
    for(auto i = pontos.begin(); i!= pontos.end();++i){
        mosaicgraph_draw_circle((*i),circle_1_color);
    }
    

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
    mosaicgraph_window_t * window = mosaicgraph_create_window(500,500,0,0);
	
	circle_1_color = (float*)malloc (3 * sizeof (float));
	circle_1_color[0] = 1.0;
	circle_1_color[1] = 0.5;
	circle_1_color[2] = 0.0;

    strcpy(window->title, "Main Page");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    mosaicgraph_draw_window(window);
    
    

    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}

