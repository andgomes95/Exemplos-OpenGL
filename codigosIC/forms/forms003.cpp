#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <vector> 
  
using namespace std; 
typedef struct color{
    float r;
    float g;
    float b;
}clr;
typedef struct objectCanvas{
    int type;
    float x0;
    float y0;
    float raio;
    clr color;
}obC;

vector<obC> objetos; 

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
int typeObject = 0;
int typeColor = 0;
float raio=0.2,distX0=0.0,distY0=0.0,distX=0.0,distY=0.0;

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
static void draw_scene(int,float,float,float,clr);
static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    for (auto i = objetos.begin(); i!= objetos.end();++i){
        draw_scene((*i).type,(*i).x0,(*i).y0,(*i).raio,(*i).color);
    }
    glutSwapBuffers();
    /*lê os pixels e salva na variavel "pixels"*/
    glReadPixels(0, 0, WIDTH, HEIGHT, FORMAT, GL_UNSIGNED_BYTE, pixels);
}

static void idle(void) {
    glutPostRedisplay();
}
static void draw_circle(float x0, float y0,float raio,clr color){
    glBegin(GL_POLYGON);
    for (int i=0; i < 360; i++){
        float degInRad = i*3.14159/180;
        glColor3f(color.r,color.g,color.b);
        glVertex2f(x0+cos(degInRad)*(raio),y0+sin(degInRad)*(raio));
    }
    glEnd();
}
static void draw_scene(int type, float x0, float y0, float raio, clr color) {
    switch(type){
        case 0:
            draw_circle(x0,y0,raio,color);
            break;        
    }    
}


void changeRaio(){
    raio = sqrt(pow(distX-distX0,2)+pow(distY-distY0,2));
}

clr createColor(){
    clr color;
    switch(typeColor){
        case 0:
            color.r = 1.0f;
            color.g = 0.0f;
            color.b = 1.0f;
            break;
        case 1:
            color.r = 1.0f;
            color.g = 1.0f;
            color.b = 0.0f;
    }
    return color;
}

void createObjectCanvas(){
    changeRaio();
    obC objeto;
    objeto.type = typeObject;
    objeto.x0 = distX0;
    objeto.y0 = distY0;
    objeto.raio = raio;
    objeto.color = createColor();
    objetos.push_back(objeto);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
            typeColor = 0;
            break;
        case 'w':
            typeColor = 1;
            break;
        case 'a': 
            typeObject = 0;
            break;
        case 's':
            typeObject = 1;
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        puts("screenshot");
        create_ppm("tmp", nscreenshots, WIDTH, HEIGHT, 255, FORMAT_NBYTES, pixels);
        nscreenshots++;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        distX0 = ((float)x/(float)HEIGHT-0.5)*2;
        distY0 = -((float)y/(float)WIDTH-0.5)*2;
        printf("%f , %f\n", distX0, distY0);
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        distX = ((float)x/(float)HEIGHT-0.5)*2;
        distY = -((float)y/(float)WIDTH-0.5)*2;
        printf("%d , %d\n", x, y);
        createObjectCanvas();
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
    glutKeyboardFunc(keyboard);
    atexit(deinit);
    glutMainLoop();
    return EXIT_SUCCESS;
}