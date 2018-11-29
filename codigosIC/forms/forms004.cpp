#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cstdio>

using namespace std;
//código pego em https://www.youtube.com/watch?v=SwPCEs9Sm9g
void renderbitmap (float x, float y, void *font, char *string);
void introscreen();
void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GLUT_SINGLE | GLUT_RGB);
    glLoadIdentity();
    glOrtho(-90.0,100.0,-15.0,100.0,0.0,1.0);
}

void display(){
   introscreen();
   glFlush();
   glutPostRedisplay(); 
}

void introscreen(){
    glColor3f(1.f,1.f,1.f);
    char buf[100] = {0};
    sprintf(buf,":::::::::::::TESTE:::::::::");
    renderbitmap(-80,40,GLUT_BITMAP_TIMES_ROMAN_10,buf);
    sprintf(buf,":::::::::::UHU:::::::::::");
    renderbitmap(-80,35,GLUT_BITMAP_TIMES_ROMAN_10,buf);
    
}

void renderbitmap (float x, float y, void *font, char *string){
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c != '\0';c++){
        glutBitmapCharacter(font,*c);
    }
}




int main (int arg, char **argv){
    glutInit(&arg,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(30,30);
    glutCreateWindow("AAAAAAAA");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}