
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
GLfloat tamCircle,movX, movY;
GLint flag;
int onMouse;
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

void mosaicgraph_draw_circle(float radius){
    glColor3f(0.8f,0.2f,0.0);
    glBegin(GL_POLYGON);
        for (int i=0; i < 360; i++){
            float degInRad = i*3.14159/180;
            glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
        }
    glEnd();
}


void display(){

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
  glLoadIdentity();
  if(flag ==1){
    glTranslatef(movX,movY,0.0);
  }
  glPushMatrix();
  mosaicgraph_draw_circle(tamCircle);
  glPopMatrix();

  glutSwapBuffers();
  glFlush();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){
      glutDestroyWindow(window);
      exit(0);
    }if (key == 65){
        tamCircle +=0.001;
    }
}
void mouseClicks(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        onMouse = 1;
        flag = 1;
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      onMouse = 0;
    }
}
void MouseAndandoNaoPressionado (int x, int y)
{
    movX = ((float)x-250.0)/250.0;
    movY = ((float)y-250.0)/250.0;
}
void MouseAndandoPressionado (int x, int y)
{
    printf("Mouse ANDANDO pressionado na janela. Posição: (%d, %d)\n", x,y);
}
void idle(){
    if(onMouse ==1){
      tamCircle +=0.001;
    }
    display();
}
int main (int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    mosaicgraph_window_t * window = mosaicgraph_create_window(500,500,0,0);
    strcpy(window->title, "Main Page");

    mosaicgraph_draw_window(window);
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutMouseFunc(mouseClicks);
    // movimento SEM botão pressionado
    glutPassiveMotionFunc(MouseAndandoNaoPressionado);

    // movimento COM botão pressionado
    glutMotionFunc(MouseAndandoPressionado);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
