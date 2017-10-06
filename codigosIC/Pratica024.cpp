#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
GLfloat rotatey=0.0,rotatex1=0.0,rotatex2=0.0,prox=1.0,angle;
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
    glTranslatef(0.0,1.5,0.0);
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
void keyPressed(unsigned char key, int x, int y) {
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
void reshapeFunc(int x, int y){
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);
}
void idleFunc(void){
    display();
}
void iluminacao(){
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]={0.2,0.2,0.2,1.0};
    GLfloat luzEspecular[4]={1.0,1.0,1.0,1.0};
    GLfloat posicaoLuz[4]={0.0,200.0,50.0,1.0};

    GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;
    glClearColor(0.0,0.0,0.0,1.0f);

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT,GL_SPECULAR,especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,luzAmbiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    angle = 45;

}
int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Pratica 24 - Braco Mecanico");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    iluminacao();
    glutMainLoop();
    return 0;
}
