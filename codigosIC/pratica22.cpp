#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
GLfloat rotate;
GLdouble size=1;
void display(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    glTranslatef(0.0,0.0,-12.0);
    glPushMatrix();
    glRotated(rotate,0.0,1.0,0.0);
    glRotated(rotate,1.0,0.0,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();
    glTranslatef(0.0f,1.0f,0.0f);
    glutSolidSphere(0.5f,30,30);
    glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }else if(key == 97){
        rotate += 1.0;
        display();
    }else if(key == 100){
        rotate -= 1.0;
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
    //rotate += 0.1;
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
    glutCreateWindow("Pratica 20 - glutSolidIcosahedron");
    rotate = 30.0;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glutFullScreen();
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
