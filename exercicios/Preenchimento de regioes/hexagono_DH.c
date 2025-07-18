#include <GL/glut.h>

void init(){
    // Define a cor de fundo da janela como branca
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // Define o sistema de coordenadas da janela (de 0 a 300 para X e Y)
    glOrtho(0, 300, 0, 300, -1, 1);
}

void desenha(){
    // Limpa o buffer de cor com a cor definida em glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    // Define a cor do desenho como azul
    glColor3f(0.0, 0.0, 1.0);

    // Inicia o desenho de um polígono
    glBegin(GL_POLYGON);
        // Vértices recalculados para um bounding box de 200x200 centrado
        glVertex2i(150, 250); // Topo
        glVertex2i(250, 200); // Superior direito
        glVertex2i(250, 100); // Inferior direito
        glVertex2i(150, 50);  // Base
        glVertex2i(50, 100);  // Inferior esquerdo
        glVertex2i(50, 200);  // Superior esquerdo
    glEnd();

    // Define a cor do texto como branco para contrastar com o azul
    glColor3f(1.0, 1.0, 1.0);

    // Posiciona e desenha a inicial 'D'
    glRasterPos2i(135, 145);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'D');

    // Posiciona e desenha a inicial 'H'
    glRasterPos2i(155, 145);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'H');

    // Força a execução de todos os comandos OpenGL pendentes
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Hexagono DH - 200x200 Bounding Box");

    init();
    glutDisplayFunc(desenha);
    glutMainLoop();

    return 0;
}