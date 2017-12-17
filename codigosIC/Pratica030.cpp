// Este código está baseado nos exemplos disponíveis no livro 
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.

#include <GL/glut.h>

GLfloat angle, fAspect;

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
            
// Função callback chamada para fazer o desenho
void Desenha(void){
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
  gluLookAt(0,80,200, 0,0,0, 0,1,0);

	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Desenha os eixos básicos na origem
	DesenhaEixos();

	glColor3f(1.0f, 0.0f, 0.0f);
	// Desenha a esfera com a cor corrente (solid)
	glPushMatrix();
		glTranslatef(-30.0f, 0.0f, 0.0f);
		glutSolidSphere(20.0f, 10, 10);
		//DesenhaEixos();
	glPopMatrix();

	glColor3f(0.0f, 1.0f, 0.0f);
	// Desenha o cubo com a cor corrente (solid)
	glPushMatrix();
		glTranslatef(30.0f, 0.0f, 0.0f);
		glutSolidCube(40.0f);
		//DesenhaEixos();
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	// Desenha o teapot com a cor corrente (solid)
	glPushMatrix();
		glTranslatef(00.0f, 40.0f, 0.0f);
		glutSolidTeapot(10.0f);
		//DesenhaEixos();
	glPopMatrix();


	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 
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
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutMainLoop();
}

