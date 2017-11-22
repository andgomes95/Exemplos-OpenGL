// Este código está baseado nos exemplos disponíveis no livro 
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.

#include <GL/glut.h>
#include <unistd.h>
#define ESCAPE 27
GLfloat angle, fAspect;
int window;
GLfloat rotate=0.0,rotatey=0.0;

void DesenhaEixos(void);
void Inicializa (void);
void EspecificaParametrosVisualizacao(GLboolean);
void AlteraTamanhoJanela(GLsizei, GLsizei);
void GerenciaMouse(int, int, int, int);
void UpdateProjection(GLboolean);

void DesenhaEixos(void)
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
}
            
void drawBody(){
    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    glScalef(2.0f,3.0f,0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawShoulder(){
    glPushMatrix();
    glColor3f(1.0f,0.5f,0.25f);
    glScalef(0.3f,0.4f,0.3f);
    glRotatef(90,-1.0f,0.0f,0.0f);
    glutSolidCone(1.0f,1.0f,10,10);
    glPopMatrix();
}
void anteHuge(){
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glScalef(0.10f,0.5f,0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void huge(){
    glTranslatef(0.0,-0.1f,0.0);
    anteHuge();
  glTranslatef(0.0,-0.3f,0.0);
    glPushMatrix();
    glColor3f(0.5f,1.0f,0.5f);
    glScalef(0.075f,0.075f,0.075f);
    glutSolidSphere(1.0f,10,10);
    glPopMatrix();
    glTranslatef(0.0,-0.25f,0.0);
    anteHuge();
}
void hand(){
    glPushMatrix();
    glColor3f(0.5f,1.0f,1.0f);
    glScalef(0.15f,0.15f,0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawHuge(){
    drawShoulder();
    glTranslatef(0.0,-0.11f,0.0);
    huge();
    glTranslatef(0.0,-0.2f,0.0);
    hand();
}
void drawLeg(){
    huge();
    glTranslatef(0.0,-0.2f,0.0);
    hand();
}
void putHuges(){
    glPushMatrix();
    glTranslatef(-1.3f,0.0f,-0.01f);
    drawHuge();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.3f,0.0f,-0.01f);
    drawHuge();
    glPopMatrix();
}
void putLegs(){
    glPushMatrix();
    glTranslatef(-0.3f,-1.6f,-0.01f);
    drawLeg();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3f,-1.6f,-0.01f);
    drawLeg();
    glPopMatrix();
}
void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.0);
    glRotatef(22,0.0,1.0,0.0);
    glRotatef(rotate,0.0f,1.0f,0.0f);
    glRotatef(rotatey,1.0f,0.0f,0.0f);
    drawBody();
    putHuges();
    putLegs();
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

// Inicializa parâmetros de rendering
void Inicializa (void){ 
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};		 // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
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
	// Define a concentração do brilho
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
	EspecificaParametrosVisualizacao(false);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(GLboolean toogle)
{
	UpdateProjection(toogle);
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

	EspecificaParametrosVisualizacao(false);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	GLboolean toogle = false;
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			toogle = !toogle;
		}
	EspecificaParametrosVisualizacao(toogle);
	glutPostRedisplay();
}

void UpdateProjection(GLboolean toggle)
{
  static GLboolean s_usePerspective = GL_TRUE;

  // toggle the control variable if appropriate
  if (toggle)
    s_usePerspective = !s_usePerspective;

  // select the projection matrix and clear it out
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // choose the appropriate projection based on the currently toggled mode
  if (s_usePerspective)
  {
    // set the perspective with the appropriate aspect ratio
    gluPerspective(angle,fAspect,5,500);
  }
  else
  {
    // set up an orthographic projection with the same near clip plane
    glOrtho(-100*fAspect, 100*fAspect, -100, 100, 5, 500);
  }

  // select modelview matrix and clear it out
  glMatrixMode(GL_MODELVIEW);
} // end UpdateProjection

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(display);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutMainLoop();
}

