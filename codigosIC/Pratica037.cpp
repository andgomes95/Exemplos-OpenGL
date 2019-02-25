
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream> // for cout
#include <math.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

        float base_2 = 0.6;
        float height_2 = 0.9;
        void cone_base_2(float value){
            base_2 = value;
        }
        void cone_height_2(float value){
            height_2 = value;
        }

typedef struct mosaicgraph_window{
        float x;
        float y;
        float width;
        float height;
        float red;
        float green;
        float blue;
        float alpha;
        float fullscreen;
        char title[128];
        int id;
        void (*process)(void *self);
}mosaicgraph_window_t;
mosaicgraph_window_t * mosaicgraph_create_window(float width, float height,float x, float y){
    mosaicgraph_window_t * window = (mosaicgraph_window_t *) malloc(sizeof(mosaicgraph_window_t));
    window->fullscreen = 0;
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    return window;
}
int mosaicgraph_draw_window(mosaicgraph_window_t * window){
    glutInitWindowPosition(window->x, window->y);
    glutInitWindowSize(window->width, window->height);
    glClearColor(window->red, window->green, window->blue, window->alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    window->id = glutCreateWindow(window->title);
    if (window->fullscreen){
        glutFullScreen();
    }
    return window->id;
}

void convert_text_to_color(const char * rgbColor, float * output){
    if (strlen(rgbColor) < 7 || rgbColor[0] != '#'){
        output[0] = 0.0;
        output[1] = 0.0;
        output[2] = 0.0;
        }

    char * r = (char*)malloc(2*sizeof(char)), * g= (char*)malloc(2*sizeof(char)), *b= (char*)malloc(2*sizeof(char));
    r[0] = rgbColor[1];
    r[1] = rgbColor[2];
    g[0] = rgbColor[3];
    g[1] = rgbColor[4];
    b[0] = rgbColor[5];
    b[1] = rgbColor[6];
    

    float ri=0.0, gi =0.0, bi =0.0;
    ri = (float) strtol(r, NULL, 16);
    gi = (float) strtol(g, NULL, 16);
    bi = (float) strtol(b, NULL, 16);


    output[0] = ri / 255.0;
    output[1] = gi / 255.0;
    output[2] = bi / 255.0;

}

        void mosaicgraph_draw_cone(float base,float height, int slices, int stacks){
            glColor3f(0.8f,0.2f,0.0);
            glutSolidCone(base,height,slices,stacks);
        }


void display(){

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);         // Limpa o collor buffer
  glLoadIdentity();
  
        mosaicgraph_draw_cone(base_2,height_2,100,100);

  glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }
    
}
void idle(){
    
    display();
}
int main (int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    mosaicgraph_window_t * window = mosaicgraph_create_window(500,500,0,0);
	
        // Color Baby!
	float color_1_color[3];
    convert_text_to_color("#010101", color_1_color);

    strcpy(window->title, "Main Page");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    mosaicgraph_draw_window(window);
    float cone_2_color[3];
    memcpy(color_1_color, cone_2_color,  sizeof(cone_2_color));



    
    glutDisplayFunc(display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
	return 0;
}
