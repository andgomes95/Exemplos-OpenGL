
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
        glVertex2f(p.x-0.01,p.y-0.01);
        glVertex2f(p.x+0.01,p.y-0.01);
        glVertex2f(p.x+0.01,p.y+0.01);
        glVertex2f(p.x-0.01,p.y+0.01);
	glEnd();
}

void auto_color(int value,int total){
    float passo=1;
    int r,g,b;
    passo = 1000/(float)total;
    passo = passo*value;
    r = passo/100;
    passo = passo -r*100;
    g = passo/10;
    b = passo - g*10;
    glColor3f((float)r/10.0,(float)g/10.0,(float)b/10.0);
}
void voronoi(){
    float x0,y0;
    list<float> distancia;
    float aux,value=88888.9;
    int indice=0, atual;
    for(int i =0;i<500;i++){
        for(int j=0;j<500;j++){
            indice=0;
            value=88888.9;
            x0 = (float)i/250.0-1.0;
            y0 = (float)j/250.0-1.0;
            for(auto i = pontos.begin(); i!= pontos.end();++i){
                aux = sqrt(pow(((*i).x-x0),2)+pow(((*i).y-y0),2));
                if(aux < value){
                    value = aux;
                    atual = indice;
                }
                indice++; 
            }
            auto_color(atual,pontos.size());
            glBegin(GL_POINTS);
            glVertex2f(x0,y0);
            glEnd();

        }
            
    }
    distancia.clear();

}

void random_points(int qtd){
    pnt aux;
    for (int i = 0;i<qtd;i++){
        aux.x = (float)(rand()%200)/100.0-1.0;
        aux.y = (float)(rand()%200)/100.0-1.0;
        pontos.push_back(aux);
    }
}


void display(){
    srand(time(NULL));
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
	glLoadIdentity();
    random_points(12);
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

