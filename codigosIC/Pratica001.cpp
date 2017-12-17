#include <GL/glut.h> 
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowPosition(1000, 0);
    glutInitWindowSize(640, 640);   // Seta resolução
    glutCreateWindow("Pratica 01 - Abrir Janela"); // Cria Janela com nome especificado
    
    glutMainLoop();           
    return 0;
}
