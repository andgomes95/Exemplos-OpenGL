#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

static GLubyte *pixels = NULL;
static const GLenum FORMAT = GL_RGBA;
static const GLuint FORMAT_NBYTES = 4;
static const unsigned int HEIGHT = 500;
static const unsigned int WIDTH = 500;
static unsigned int nscreenshots = 0;
static unsigned int time;

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
    time = glutGet(GLUT_ELAPSED_TIME);
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

    glBegin(GL_POLYGON);
    float a = 0.0, b = 0.0, c = 0.0;
    for (int i=0; i < 360; i++){
        float degInRad = i*3.14159/180;
        if (a < 1.0){
            a = a+0.1;
        }else if (a > 1.0 && b < 1.0){
            b = b + 0.1;
        }else if(a > 1.0 && b > 1.0 && c < 1.0){
            c = c + 0.1;
        }else {
            a = 0.0;
            b = 0.0;
            c = 0.0;
        }
        glColor3f(b,a,c);
        glVertex2f(cos(degInRad)*(0.5+0.2),sin(degInRad)*(0.5+0.6));
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
    if (state == GLUT_DOWN) {
        puts("screenshot");
        create_ppm("tmp", nscreenshots, WIDTH, HEIGHT, 255, FORMAT_NBYTES, pixels);
        nscreenshots++;
    }
}

int main(int argc, char **argv) {
    GLint glut_display;
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    atexit(deinit);
    glutMainLoop();
    return EXIT_SUCCESS;
}