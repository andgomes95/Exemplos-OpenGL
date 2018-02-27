#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

GLfloat xRotated, yRotated, zRotated;
GLdouble size=1;
void legs(){
    glutSolidSphere(0.1f,20,20);
    glPushMatrix();
    glTranslatef(1.0f,-0.0f,4.0f);
    //glColor3f(1.0,0.5,0.5);
    glutSolidSphere(0.1f,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f,1.5f,0.0f);
    glutSolidSphere(0.1f,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f,3.0f,0.0f);
    glutSolidSphere(0.1f,20,20);
    glPopMatrix();
}

void points(){
    glPushMatrix();
    glutSolidSphere(0.1f,20,20);
    glTranslatef(0.0,-1.0,-1.0);
    glutSolidSphere(0.1f,20,20);
    glTranslatef(0.0,-1.0,2.0);
    glutSolidSphere(0.1f,20,20);
    glPopMatrix();
}

void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-4.0,-1.0,-18.0);
    glutSolidSphere(0.1f,20,20);
    glPushMatrix();
    glTranslatef(-1.0,-3.0,0.0);
    legs();
    glTranslatef(2.0,0.0,0.0);
    legs();
    glPopMatrix();
    glTranslatef(0.0,1.0,-1.0);
    glutSolidSphere(0.1f,20,20);
    glTranslatef(0.0,1.0,2.0);
    glutSolidSphere(0.1f,20,20);
    glTranslatef(0.0,1.0,-1.0);
    glutSolidSphere(0.1f,20,20);
    glPushMatrix();
    glTranslatef(-1.0,0.0,0.0);
    points();
    glTranslatef(2.0,0.0,0.0);
    points();
    glPopMatrix();
    glTranslatef(0.0,1.0,1.0);
    glutSolidSphere(0.1f,20,20);
    glFlush();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }
}
void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);
}

void idleFunc(void)
{
     xRotated += 0.01;
     yRotated += 0.01;
     zRotated += 0.01;    
    display();
}


int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    //double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    // window sizer
    glutInitWindowSize(400,350);
    // create the window 
    glutCreateWindow("Pratica 19 - glutSolidTetrahedron");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    xRotated = yRotated = zRotated = 30.0;
    glClearColor(0.0,0.0,0.0,0.0);
    //Assign  the function used in events
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    //Let start glut loop
    glutMainLoop();
    return 0;
}
