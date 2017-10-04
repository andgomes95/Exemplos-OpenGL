#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

GLfloat xRotated, yRotated, zRotated,xPosition;
GLdouble size=1;

void createTexture(SDL_Surface* image)
{   
   //Criamos um objeto de textura e obtemos seu id
    int id = 0;    glGenTextures(1, &id); 
 
    //Dizemos a OpenGL que iremos trabalhar com o objeto.
   glBindTexture(GL_TEXTURE_2D, id);
 
    //Filtro. Veremos isso nos próximos artigos.
   glTexParameteri(GL_TEXTURE_2D,
      GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 
    //Descobrimos o formato a partir da imagem
   GLint format =
      image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;
 
    //Carregamos a imagem do disco
   glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
        format, GL_UNSIGNED_BYTE, image->pixels);
 
    //Como a OpenGL copiou a imagem, apagamos a SDL_Image.
   SDL_FreeSurface(image);
}
void display(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-10.0);
    // Flush buffers to screen
    glPushMatrix();
    glTranslatef(0.0,0.0,1.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glColor3f(xPosition, 0.2, 0.1); 
    glutSolidCube(2.0f); //double tamanho de uma aresta
    glPopMatrix();
    glFlush();        
    // sawp buffers called because we are using double buffering 
    glutSwapBuffers();
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
    // xPosition = (xPosition < 1.0f)? xPosition + 0.01f : -1.0f;
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
    glutCreateWindow("Pratica 24 - Texture");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    xRotated = yRotated = zRotated = 30.0;
    xPosition = -1.0f;
    
    glutFullScreen();
    glClearColor(0.0,0.0,0.0,0.0);
    //textura
    //Assign  the function used in events
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    //Let start glut loop
    glutMainLoop();
    return 0;
}
