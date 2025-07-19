#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.1415
#define N_VERTICES 4

// Prototipação das funções
void display(void);
void atualizaH(int);
void HSI_to_RGB(float H, float S, float I, float* R, float* G, float* B);

// Vetor com os valores de Hue para cada vértice (inicializados)
float H_values[N_VERTICES] = {0.0f, 90.0f, 180.0f, 270.0f};
/* um vetor com as matizes (H) de cada vértice,
 começando com valores espaçados de 90° para obter
 cores bem distintas no início.
*/

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(256, 256);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    // Definindo fundo branco
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // glShadeModel(GL_FLAT); 
    glShadeModel(GL_SMOOTH);   // Definido o modo SMOOTH

    glOrtho(0, 1, 0, 1, -1, 1);

    glutDisplayFunc(display);

    // Adicionei um temporizador para atualizar as cores
    glutTimerFunc(33, atualizaH, 1);

    glutMainLoop();
    return 0;
}

void atualizaH(int value) {
    // Atualiza as matizes (H) de cada vértice
    for (int i = 0; i < N_VERTICES; i++) {
        H_values[i] += 1.0f;  // Incremento de 1° por frame
        if (H_values[i] >= 360.0f)
            H_values[i] -= 360.0f;
    }

    glutPostRedisplay();              // Solicita redesenho
    glutTimerFunc(33, atualizaH, 1);      // Reativa o timer para animação contínua
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);

    // Para cada vértice, calcula a cor HSI para RGB e define antes de desenhar
    for (int i = 0; i < N_VERTICES; i++) {
        float R, G, B;
        HSI_to_RGB(H_values[i], 1.0f, 1.0f, &R, &G, &B);  // Saturação e Intensidade máximas
        glColor3f(R, G, B);

        // Define a posição de cada vértice
        switch (i) {
            case 0: glVertex2f(0.25, 0.25); break;  // inferior esquerdo
            case 1: glVertex2f(0.75, 0.25); break;  // inferior direito
            case 2: glVertex2f(0.75, 0.75); break;  // superior direito
            case 3: glVertex2f(0.25, 0.75); break;  // superior esquerdo
        }
    }

    glEnd();
    glFlush();
/*
 No display, criei um loop para os 4 vértices:
 - Calcula a cor HSI → RGB
 - Define a cor
 - Posiciona o vértice
 Isso permite que cada vértice tenha sua própria cor variável.*/

}



// Função para converter HSI para RGB
void HSI_to_RGB(float H, float S, float I, float* R, float* G, float* B) {
    float r, g, b;
    float radH = H * M_PI / 180.0f;  // Converte H de graus para radianos

    // caculo da cor RGB baseado no modelo HSI
    if (H < 120.0f) {
        r = I * (1 + (S * cos(radH)) / (cos(M_PI / 3 - radH)));
        g = I * (1 + (S * (1 - (cos(radH)) / (cos(M_PI / 3 - radH)))));
        b = I * (1 - S);
    } else if (H < 240.0f) {
        H -= 120.0f;
        radH = H * M_PI / 180.0f;
        g = I * (1 + (S * cos(radH)) / (cos(M_PI / 3 - radH)));
        b = I * (1 + (S * (1 - (cos(radH)) / (cos(M_PI / 3 - radH)))));
        r = I * (1 - S);
    } else {
        H -= 240.0f;
        radH = H * M_PI / 180.0f;
        b = I * (1 + (S * cos(radH)) / (cos(M_PI / 3 - radH)));
        r = I * (1 + (S * (1 - (cos(radH)) / (cos(M_PI / 3 - radH)))));
        g = I * (1 - S);
    }

    // Garante valores entre 0 e 1
    *R = r < 0.0f ? 0.0f : (r > 1.0f ? 1.0f : r);
    *G = g < 0.0f ? 0.0f : (g > 1.0f ? 1.0f : g);
    *B = b < 0.0f ? 0.0f : (b > 1.0f ? 1.0f : b);




}

