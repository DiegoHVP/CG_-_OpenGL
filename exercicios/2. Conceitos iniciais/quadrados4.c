#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

/* Função de desenho */
void display(void);

int main(int argc, char** argv) {
    // Inicializa GLUT
    glutInit(&argc, argv);
    // Define o modo de display: 1 buffer e RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Define o tamanho da janela
    glutInitWindowSize(256, 256);
    // Define a posição inicial da janela
    glutInitWindowPosition(100, 100);
    // Cria a janela com o título vindo do argumento
    glutCreateWindow(argv[0]);

    // Define a cor de fundo da janela: branco
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // Define o modelo de cor
    glShadeModel(GL_FLAT);
    // Define a área de visualização ortogonal
    glOrtho(0, 1, 0, 1, -1, 1);

    // Define a função de callback para exibir
    glutDisplayFunc(display);
    // Entra no loop de eventos
    glutMainLoop();
    return 0;
}

void display(void) {
    // Limpa o buffer de cor
    glClear(GL_COLOR_BUFFER_BIT);

    // DESENHO DO 1º QUADRADO (vermelho)
    glColor3f(1.0, 0.0, 0.0);  // cor vermelha
    glBegin(GL_POLYGON);
        glVertex2f(0.05, 0.55);  // canto inferior esquerdo
        glVertex2f(0.45, 0.55);  // canto inferior direito
        glVertex2f(0.45, 0.95);  // canto superior direito
        glVertex2f(0.05, 0.95);  // canto superior esquerdo
    glEnd();

    // DESENHO DO 2º QUADRADO (verde)
    glColor3f(0.0, 1.0, 0.0);  // cor verde
    glBegin(GL_POLYGON);
        glVertex2f(0.55, 0.55);
        glVertex2f(0.95, 0.55);
        glVertex2f(0.95, 0.95);
        glVertex2f(0.55, 0.95);
    glEnd();

    // DESENHO DO 3º QUADRADO (azul)
    glColor3f(0.0, 0.0, 1.0);  // cor azul
    glBegin(GL_POLYGON);
        glVertex2f(0.05, 0.05);
        glVertex2f(0.45, 0.05);
        glVertex2f(0.45, 0.45);
        glVertex2f(0.05, 0.45);
    glEnd();

    // DESENHO DO 4º QUADRADO (amarelo)
    glColor3f(1.0, 1.0, 0.0);  // cor amarela
    glBegin(GL_POLYGON);
        glVertex2f(0.55, 0.05);
        glVertex2f(0.95, 0.05);
        glVertex2f(0.95, 0.45);
        glVertex2f(0.55, 0.45);
    glEnd();

    // Finaliza os comandos de desenho
    glFlush();
}
