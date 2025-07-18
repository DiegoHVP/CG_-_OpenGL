#include <GL/glut.h>
#include <stdlib.h>




// 0 = bresenham linha | 1 = bresenham circunferência
int modo = 0;
void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0); // fundo branco
  glOrtho(0, 256, 0, 256, -1, 1);   // define coordenadas 2D
}

// tag::line[]
void bresenhamLine(int x0, int y0, int x1, int y1){
// dadas as coordenadas (x0, y0) e (x1, y1),
// desenha uma linha entre esses pontos usando o algoritmo de Bresenham    
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  glBegin(GL_POINTS); // desenha ponto a ponto
// loop até chegar no ponto final
  while (1){
    glVertex2i(x0, y0); // plota ponto atual

    if (x0 == x1 && y0 == y1) break; // chegou no final
    // calcula o erro
    int e2 = 2 * err;
    if (e2 > -dy){ err -= dy; x0 += sx; }
    if (e2 < dx){ err += dx; y0 += sy; }
  }
  glEnd();
}
// end::line[]


// tag::circle[]
void bresenhamCircuferencia(int xc, int yc, int r){
  // dadas as coordenadas do centro (xc, yc) e o raio r,
  // desenha uma circunferência usando o algoritmo de Bresenham
  int x = 0, y = r;
  int d = 3 - 2 * r;

  glBegin(GL_POINTS); // desenha ponto a ponto
  while (y >= x){
    // Desenha os 8 pontos simétricos

    // as partes invertidas são necessárias
    // para desenhar a circunferência completa  
    // pois sem elas, só desenharíamos
    // a parte superior direita da circunferência.


    glVertex2i(xc + x, yc + y); // ponto superior direito
    glVertex2i(xc - x, yc + y); // ponto superior esquerdo
    glVertex2i(xc + x, yc - y); // ponto inferior direito
    glVertex2i(xc - x, yc - y); // ponto inferior esquerdo
    glVertex2i(xc + y, yc + x); // ponto superior direita invertida
    glVertex2i(xc - y, yc + x); // ponto superior esquerda invertida
    glVertex2i(xc + y, yc - x); // ponto inferior direita invertida
    glVertex2i(xc - y, yc - x); // ponto inferior esquerda invertida

    // Atualiza o erro
    // Se o erro for positivo, diminui y
    // Se o erro for negativo, mantém y
    // e aumenta x
    x++;
    if (d > 0){
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
  }
  glEnd();
}
// end::circle[]


void display(void){
    // Limpa a tela
    glClear(GL_COLOR_BUFFER_BIT);

    // Verifica o modo de desenho
  if (modo == 0){
    // Desenha linha verde
    glColor3f(0.0, 1.0, 0.0);
    bresenhamLine(40, 200, 200, 10);
  } else if (modo == 1){
    // Desenha circunferência azul
    glColor3f(0.0, 0.0, 1.0);
    bresenhamCircuferencia(128, 128, 50);
  }

  glFlush();
}


void keyboard(unsigned char key, int x, int y){
  switch (key){
    case 'l':  // modo linha
      modo = 0;
      glutPostRedisplay();
      break;
    case 'c':  // modo circunferência
      modo = 1;
      glutPostRedisplay();
      break;
    case 27:   // tecla ESC
      exit(0);
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(256, 256);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Bresenham");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
