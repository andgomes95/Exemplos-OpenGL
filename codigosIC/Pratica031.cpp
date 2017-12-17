#include <GL/gl.h>
#include <GL/glut.h>

GLfloat angle = 0.0;

GLfloat density = 0.3;
GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};

void cube (void) {
    glRotatef(angle, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(2);
}

void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_LINEAR);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    cube();
    glutSwapBuffers();
    angle ++;
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0)
;
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
    if (key=='a') {
    glFogi (GL_FOG_MODE, GL_EXP);
    }
    if (key=='s') {
    glFogi (GL_FOG_MODE, GL_EXP2);
    }
    if (key=='d') {
    glFogi (GL_FOG_MODE, GL_LINEAR);
    }
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH
);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutMainLoop ();
    return 0;
}