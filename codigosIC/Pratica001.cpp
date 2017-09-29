#include <GL/glut.h> 
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("Pratica 01 - Abrir Janela"); // Cria Janela com nome especificado
    glutInitWindowSize(640, 640);   // Seta resolução
    glutInitWindowPosition(0, 0); // Posição inicial na tela
    glutMainLoop();           
    return 0;
}