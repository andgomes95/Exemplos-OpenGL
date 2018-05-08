#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#define ESCAPE 27
int window;

GLfloat xRotated, yRotated, zRotated;
GLdouble size=1;

void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
  //  glTranslatef(0.0,0.0,-4.5);
    glColor3f(0.8, 0.2, 0.1);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(1.0f);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){
      glutDestroyWindow(window);
      exit(0);
    }
}
/*void reshapeFunc(int x, int y){
    if (y == 0 || x == 0) return;
      glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);
}*/
void idleFunc(void){
     xRotated += 0.0;
     yRotated += 0.0;
     zRotated += 0.0;
    display();
}
int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutCreateWindow("Pratica 14 - Cubo");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    xRotated = yRotated = zRotated = 30.0;
  //  glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
  //  glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
    return 0;
}
