#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

GLfloat xRotated, yRotated, zRotated;
GLdouble size=1;


void display(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-4.5);
    // Red color used to draw.
    glTranslatef(-1.0,0.0,0.0);
    glColor3f(1, 1, 1); 
    glutSolidTeapot(1.0f);

    glTranslatef(2.0,0.0,0.0);
    glColor3f(1, 1, 0); 
    glutSolidTeapot(1.0f);

    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a Teapot.
    /*******AQUI MODIFICAÇÃO PRINCIPAL*******/
//    glutSolidSphere(1.0f,100,200); //double raio, int pedaços em volta do eixo Z,  int pedaços percorrendo o eixo Z
    // Flush buffers to screen
    
    glColor3f(1, 0, 00); 
    glRotatef(0,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(0,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(0,0.0,0.0,1.0);
    glutSolidTeapot(1.0f);

    glFlush();        
    // sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }//se pressionar esc, saiu
}
void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
 
    glViewport(0,0,x,y);  //Use the whole window for rendering
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
    // window size
    glutInitWindowSize(400,350);
    // create the window 
    glutCreateWindow("Pratica 13 - Esfera");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
