#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include <unistd.h>
#include <iostream> // for cout
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

static GLubyte *pixels = NULL;
static const GLenum FORMAT = GL_RGBA;
static const GLuint FORMAT_NBYTES = 4;
static const unsigned int HEIGHT = 500;
static const unsigned int WIDTH = 500;
static unsigned int nscreenshots = 0;
static unsigned int timee;

/* Model. */
static double angle = 0;
static double angle_speed = 45;

static void init(void)  {
    glReadBuffer(GL_BACK);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1); 
    /*(definir modos de armazenamento em pixels - 
        1º parametro -  pname: Especifica o nome simbólico do parâmetro a ser definido.
            Um valor afeta o empacotamento de dados de pixel na memória: GL_PACK_ALIGNMENT.
            O outro afeta a descompactação de dados de pixel da memória: GL_UNPACK_ALIGNMENT.)
        2º parametro - param: Especifica o valor para o qual pname está definido.*/
    glViewport(0, 0, WIDTH, HEIGHT);
    /* Seta a janela de exibição
    Parametros: GLint x,  GLint y,  GLsizei width,  GLsizei height*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    pixels = (GLubyte*)malloc(FORMAT_NBYTES * WIDTH * HEIGHT);
    timee = glutGet(GLUT_ELAPSED_TIME);
    /*glutGet recupera o estado GLUT simples representado por inteiros.
    GLUT_ELAPSED_TIME: Número de milissegundos desde que glutInit chamou (ou primeira chamada para glutGet (GLUT_ELAPSED_TIME)).
    */
}

static void deinit(void)  {
    /*liberar pixels*/
    free(pixels);
}
/* Funcao que cria o print screen*/
static void create_ppm(char *prefix, int frame_id, unsigned int width, unsigned int height,
        unsigned int color_max, unsigned int pixel_nbytes, GLubyte *pixels) {
    size_t i, j, k, cur;
    enum Constants { max_filename = 256 };
    char filename[max_filename];
    snprintf(filename, max_filename, "%s%d.ppm", prefix, frame_id);
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, HEIGHT, 255);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cur = pixel_nbytes * ((height - i - 1) * width + j);
            
            fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

static void draw_scene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    float x,y,z;
    int j;
    glBegin(GL_POLYGON);
    glColor3f(1.0,0,0);
    for (int i=0; i < 360; i++){
        float degInRad = i*3.14159/180;
 //       j=0;
//        for(j = 0; j <180;j++){
            float degInRad2 = 20*3.14159/180;
            x = sin(degInRad2)*cos(degInRad)*(0.2+0.05)+0.1;
            y = sin(degInRad2)*sin(degInRad)*(0.2+0.1)-0.1;
            z = 0.1+(0.2)*sin(degInRad);
            glVertex3f(x,y,z);
  //      }
        
    }
    glEnd();
    
}

static void display(void) {
    draw_scene();
    glutSwapBuffers();
    /*lê os pixels e salva na variavel "pixels"*/
    glReadPixels(0, 0, WIDTH, HEIGHT, FORMAT, GL_UNSIGNED_BYTE, pixels);
}

static void idle(void) {
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        puts("screenshot");
        create_ppm("tmp", nscreenshots, WIDTH, HEIGHT, 255, FORMAT_NBYTES, pixels);
        nscreenshots++;
    }
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }

}

int main(int argc, char **argv) {
    GLint glut_display;
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutKeyboardFunc(&keyPressed);
    atexit(deinit);
    glutMainLoop();
    return EXIT_SUCCESS;
}