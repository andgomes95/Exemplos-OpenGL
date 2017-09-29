#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
void drawPoint(){
	glBegin(GL_POINTS);
	glColor3f(0.8f,0.2f,0.0);
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			glVertex2f(0.1f*(float)i-1.0f,0.1f*(float)j-1.0f);
		}
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
  drawPoint();
  glutSwapBuffers();  // Renderizar
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    window = glutCreateWindow("Pratica 04 - GL_POINTS"); // Cria Janela com nome especificado
    glutInitWindowSize(640, 640);   // Seta resolução
    glutInitWindowPosition(0, 0); // Posição inicial na tela
    glutFullScreen();//Seta FullScreen
    glutDisplayFunc(display);
    glutIdleFunc(&display);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();           
    return 0;
}