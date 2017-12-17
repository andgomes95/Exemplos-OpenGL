#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;
GLfloat rotate=0.0,rotatey=0.0;
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
void drawLegDeslocated(){
    anteHuge();
    glTranslatef(0.0,-0.3f,0.0);
    glPushMatrix();
    glColor3f(0.5f,1.0f,0.5f);
    glScalef(0.075f,0.075f,0.075f);
    glutSolidSphere(1.0f,10,10);
    glPopMatrix();
    glTranslatef(0.25f,0.0,0.0);
    glRotatef(90,0,0,1);
    anteHuge();
    glTranslatef(0.00f,-0.2f,0.0);
  //  glTranslatef(0.2f,0.0,0.0);
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
    /*
    drawBody();
    putHuges();
    putLegs();*/
    drawLegDeslocated();
    glFlush();
    glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){
      glutDestroyWindow(window);
      exit(0);
  }else if(key == 97){
      rotate += 2.0f;
  }else if(key == 115){
      rotatey += 2.0f;
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
int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Pratica 25 - Bob Esponja");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.5,0.5,1.0,0.5);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
    return 0;
}
