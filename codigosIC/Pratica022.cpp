#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>

#define QTDGOTAS 1000

int loop;

typedef struct {
    bool viva;
    float vida;
    float desaparecer;
    float xPos;
    float yPos;
    float zPos;
    float vel;
    float gravidade;
} structGota;


structGota Gota[QTDGOTAS];

void iniciaGota(int i) {
    Gota[i].viva = true;
    Gota[i].vida = 1.5;
    Gota[i].desaparecer = float(rand() % 100) * 0.001;
    Gota[i].xPos = (float) (rand() % 40) - 10;
    Gota[i].yPos = 15.0; //altura de onde começa as gotas
    Gota[i].zPos = (float) (rand() % 20) - 10;
    Gota[i].vel = 0.001;
    Gota[i].gravidade = -0.01;
}

void init() {
    for (loop = 0; loop < QTDGOTAS; loop++) {
        iniciaGota(loop);
    }
}

void criaChuva() {
    float x, y, z;
    for (loop = 0; loop < QTDGOTAS; loop = loop + 2) {
        if (Gota[loop].viva == 1) {
            x = Gota[loop].xPos;
            y = Gota[loop].yPos;
            z = Gota[loop].zPos - 25;

            glBegin(GL_LINES);
            glVertex3f(x -1, y, z); //faz as linhas ficarem em 90º com o x-1
            glVertex3f(x, y + 1, z); //Tamanho da gota é o 1
            glEnd();

            Gota[loop].yPos += Gota[loop].vel;
            Gota[loop].xPos += Gota[loop].vel;
            Gota[loop].vel += Gota[loop].gravidade;
            Gota[loop].vida -= Gota[loop].desaparecer;

            if (Gota[loop].vida < 0.0) {
                iniciaGota(loop);
            }
        }
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glEnd();
    criaChuva();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) w / (float) h, .1, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 480); //tamanho da tela
    glutCreateWindow("Pratica 22 - Chuva");
    init(); //inicia o glut
    glutDisplayFunc(drawScene); //callback, qual função vai ser chamada para mostrar
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
