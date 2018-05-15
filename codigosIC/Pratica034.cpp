#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
time_t tim;
GLfloat xRotated,yRotated,zRotated;
void drawVerticalFundo(){
	glBegin(GL_LINES);
	for(int i=0;i<21;i++){
    glColor3f(float(rand()%20)/20.0,float(rand()%20)/20.0,float(rand()%20)/20.0);
		glVertex3f(0.1f*(float)i-1.0f,1.0,-1.0);
    glColor3f(float(rand()%20)/20.0,float(rand()%20)/20.0,float(rand()%20)/20.0);
    glVertex3f(0.1f*(float)i-1.0f,-1.0,-1.0);
	}
	glEnd();
}
void drawHorizontalFundo(){
	glBegin(GL_LINES);
	for(int i=0;i<21;i++){
    glColor3f(float(rand()%20)/20.0,float(rand()%20)/20.0,float(rand()%20)/20.0);
		glVertex3f(1.0,0.1f*(float)i-1.0f,-1.0);
    glColor3f(float(rand()%20)/20.0,float(rand()%20)/20.0,float(rand()%20)/20.0);
    glVertex3f(-1.0,0.1f*(float)i-1.0f,-1.0);
	}
	glEnd();
}
void drawVerticalFundo0(){
	glBegin(GL_LINES);glColor3f(float(rand()%20)/20.0,float(rand()%20)/20.0,float(rand()%20)/20.0);
  glColor3f(0.7,0.2,0.7);
	for(int i=0;i<21;i++){
    glVertex3f(0.1f*(float)i-1.0,1.0,-1.0f);
    glVertex3f(0.1f*(float)i-1.0,1.0,1.0f);
	}
	glEnd();
}
void drawHorizontalFundo0(){
	glBegin(GL_LINES);
  glColor3f(0.0,1.0,0.0);
	for(int i=0;i<21;i++){
    glVertex3f(-1.0,1.0,0.1f*(float)i-1.0f);
    glVertex3f(1.0,1.0,0.1f*(float)i-1.0f);
	}
	glEnd();
}
void drawVerticalFundo1(){
	glBegin(GL_LINES);
  glColor3f(0.0,1.0,1.0);
	for(int i=0;i<21;i++){
    glVertex3f(0.1f*(float)i-1.0,-1.0,-1.0f);
    glVertex3f(0.1f*(float)i-1.0,-1.0,1.0f);
	}
	glEnd();
}
void drawHorizontalFundo1(){
	glBegin(GL_LINES);
  glColor3f(1.0,0.0,1.0);
	for(int i=0;i<21;i++){
    glVertex3f(-1.0,-1.0,0.1f*(float)i-1.0f);
    glVertex3f(1.0,-1.0,0.1f*(float)i-1.0f);
	}
	glEnd();
}
void drawVerticalFundo2(){
	glBegin(GL_LINES);
  glColor3f(1.0,1.0,1.0);
	for(int i=0;i<21;i++){
    glVertex3f(1.0,0.1f*(float)i-1.0,-1.0f);
    glVertex3f(1.0,0.1f*(float)i-1.0,1.0f);
	}
	glEnd();
}
void drawHorizontalFundo2(){
	glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0f);
	for(int i=0;i<21;i++){
    glVertex3f(1.0,1.0,0.1f*(float)i-1.0f);
    glVertex3f(1.0,-1.0,0.1f*(float)i-1.0f);
	}
	glEnd();
}
void drawVerticalFundo3(){
	glBegin(GL_LINES);
  glColor3f(1.0,1.0,0.0);
	for(int i=0;i<21;i++){
    glVertex3f(-1.0,0.1f*(float)i-1.0,-1.0f);
    glVertex3f(-1.0,0.1f*(float)i-1.0,1.0f);
	}
	glEnd();
}
void drawHorizontalFundo3(){
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	for(int i=0;i<21;i++){
    glVertex3f(-1.0,1.0,0.1f*(float)i-1.0f);
    glVertex3f(-1.0,-1.0,0.1f*(float)i-1.0f);
	}
	glEnd();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){
      glutDestroyWindow(window);
      exit(0);
    }//se pressionar esc, saiu
}
void reshapeFunc(int x, int y){
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);
}
void cube(){
  drawVerticalFundo();
  drawHorizontalFundo();
  drawVerticalFundo0();
  drawHorizontalFundo0();
  drawVerticalFundo1();
  drawHorizontalFundo1();
  drawVerticalFundo2();
  drawHorizontalFundo2();
  drawVerticalFundo3();
  drawHorizontalFundo3();
}
void display(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Seta Background
  glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
  glTranslatef(0.0f,0.0f,-0.001f);      //muglColor3f(float(rand()%20)/20.0,float(rand()%20)/20.0,float(rand()%20)/20.0);da a perspectiva
  glRotatef(xRotated,1.0f,0.0f,0.0f);
  glRotatef(yRotated,0.0f,1.0f,0.0f);
  glRotatef(zRotated,0.0f,0.0f,1.0f);
  cube();
  glPushMatrix();
  glTranslatef(0.0f,0.0f,1.0f);
  cube();
  glPopMatrix();
  glutSwapBuffers();  // Renderizar
}
void idleFunc(void)
{

    // xRotated += 0.001;
    // yRotated += 0.001;
     zRotated += 0.001;

    display();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    window = glutCreateWindow("Box"); // Cria Janela com nome especificado
    glutInitWindowSize(640, 640);   // Seta resolução
    xRotated = yRotated = zRotated = 0.0;
    glutInitWindowPosition(0, 0); // Posição inicial na tela
    glutFullScreen();//Seta FullScreen
    srand((unsigned) time(&tim));
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(&idleFunc);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
    return 0;
}
