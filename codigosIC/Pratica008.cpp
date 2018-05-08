#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#include <math.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
void mosaicgraph_draw_circle(float radius,float elipse_x,float elipse_y){
    glColor3f(0.8f,0.2f,0.0);
    glBegin(GL_POLYGON);       
        for (int i=0; i < 360; i++){
            float degInRad = i*3.14159/180;
            glVertex2f(cos(degInRad)*(radius+elipse_x),sin(degInRad)*(radius+elipse_y));
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
void display(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Seta Background
  glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
  //glTranslatef(0.0f,0.0f,-1.0f);      //muda a perspectiva
  mosaicgraph_draw_circle(0.4,0.2,-0.2);
  glutSwapBuffers();  // Renderizar
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    window = glutCreateWindow("Pratica 8 - GL_POLYGON"); // Cria Janela com nome especificado
    glutInitWindowSize(640, 640);   // Seta resolução
    glutInitWindowPosition(0, 0); // Posição inicial na tela
    //glutFullScreen();//Seta FullScreen
    glutDisplayFunc(display);
    glutIdleFunc(&display);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();           
    return 0;
}