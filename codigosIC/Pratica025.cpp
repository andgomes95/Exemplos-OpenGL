// Este código está baseado nos exemplos disponíveis no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#define ESCAPE 27
int window;
GLfloat angle, fAspect;
GLfloat rotatey=0.0,rotatex1=0.0,rotatex2=0.0,prox=1.0;
void drawBrace(){
    glTranslatef(0.0,1.5,0.0);
    glPushMatrix();
    glColor3f(0.4, 0.3, 0.6);
    glScalef(1.0,2.5,1.0);
    glutSolidCube(1.0f);
    glPopMatrix();
    glTranslatef(0.0,1.5,0.0);
}
void drawEixo(){
    glPushMatrix();
    glScalef(0.5f,0.5f,0.5f);
    glColor3f(0.1,0.4,0.2);
    glutSolidSphere(1.0f,10,10);
    glPopMatrix();
}
void drawCube(){
    glPushMatrix();
    glColor3f(0.4, 0.2, 0.1);
    glScalef(3.0,3.0,3.0);
    glutSolidCube(1.0f); //double tamanho de uma aresta
    glPopMatrix();
}
void drawPalma(){
    glPushMatrix();
    glScalef(3.0,1.0,0.4);
    glColor3f(1.0f,1.0f,1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawFinger(){
    glRotatef(90,0.0f,1.0f,0.0);
    glPushMatrix();
    glScalef(0.1,1.0,0.1);
    glColor3f(1.0f,0.0f,0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawHand(){
        drawPalma();
        glPushMatrix();
        glTranslatef(prox,0.75f,0.0f);
        drawFinger();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-prox,0.75f,0.0f);
        drawFinger();
        glPopMatrix();
}
void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
    glLoadIdentity();
    glTranslatef(-2.5,-2.5,-15.0);
    drawCube();
    glTranslatef(0.0,2.0	,0.0);
    glRotatef(rotatey,0.0,1.0,0.0);
    glRotatef(rotatex1,1.0,0.0,0.0);
    drawEixo();
    glRotatef(-22.5,0.0,0.0,1.0);
    drawBrace();
    glRotatef(-65.5,0.0,1.0,1.0);
    glRotatef(rotatex2,1.0,0.0,0.0);
    glRotatef(rotatey,0.0,1.0,0.1);
    drawEixo();
    drawBrace();
    glTranslatef(0.0f,0.2f,0.0f);
    glRotatef(rotatey,0.0,1.0,0.0);
    drawHand();
    glFlush();
    glutSwapBuffers();
}
// Inicializa parâmetros de rendering
void Inicializa (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};		 // "cor"
	GLfloat luzEspecular[4]={0.5, 0.5, 0.5, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// DefiInicializane a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=45;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
    gluPerspective(angle,fAspect,0.4,500);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
void idleFunc(void){
    display();
}void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){
      glutDestroyWindow(window);
      exit(0);
  }else if(key == 97){
      rotatex1 += 1.0;
  }else if (key == 115){
      rotatex2 += 1.0;
  }else if (key == 113){
      rotatex1 -= 1.0;
  }else if (key == 119){
      rotatex2 -= 1.0;
  }else if (key == 101){
      rotatey += 1.0;
  }else if (key == 100){
      rotatey -= 1.0;
  }else if (key == 122){
      if(prox > 0.06){
          prox -= 0.01;
      }
  }else if(key == 120){
      if(prox < 1.0){
          prox += 0.01;
      }
  }
}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(display);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(&keyPressed);
	Inicializa();
	glutMainLoop();
}
