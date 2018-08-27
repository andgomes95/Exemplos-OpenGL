#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)        // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);    // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(50.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}
void drawQuadrado(){
  glBegin(GL_LINE_STRIP);
      glVertex3f(0.5f,0.5f,0.0f);
        glVertex3f(-0.5f,0.5f,0.0f);
        glVertex3f(-0.5f,-0.5f,0.0f);
        glVertex3f(0.5f,-0.5f,0.0f);
  glEnd();
}

void drawTriangulo(){
    glBegin(GL_LINE_STRIP);
      glVertex3f(0.5f,0.0f,0.0f);
        glVertex3f(0.0f,1.0f,0.0f);
        glVertex3f(-0.5f,0.0f,0.0f);
  glEnd();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }//se pressionar esc, saiu
}
void display(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Seta Background
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Limpa o collor buffer
  glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 500.0);
  glPushMatrix();

  glTranslatef(1.0f,1.0f,0.0f);
  glRotatef(45,0.0f,0.0f,1.0);
  glScalef(2.0f,3.0f,0.0f);
  drawQuadrado();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(1.0f,1.0f,-6.0f);
  glRotatef(180,0.0f,0.0f,1.0);
  glScalef(2.0f,3.0f,0.0f);
  drawTriangulo();
  glPopMatrix();
//  glTranslatef(0.0f,0.0f,-6.0f);
   
  glutSwapBuffers();  // Renderizar
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    glutInitWindowSize(640, 480);   // Seta resolução
    window = glutCreateWindow("Pratica 006"); // Cria Janela com nome especificado
    glutDisplayFunc(display);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();           
    return 0;
}
