#include <GL/glut.h>
#include <stdlib.h>

float cor[3] = {1.0, 0.0, 0.0}; // cor inicial: vermelho

void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(0, 256, 0, 256, -1, 1);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3fv(cor); // aplica cor atual
  
  glBegin(GL_QUADS);
    glVertex2i(30, 226);
    glVertex2i(226, 226);
    glVertex2i(226, 30);
    glVertex2i(30, 30);
  glEnd();
  
  glFlush();
}

void keyboard(unsigned char key, int x, int y){
  switch (key){
    case 'a': // azul
      cor[0] = 0.0; cor[1] = 0.0; cor[2] = 1.0;
      glutPostRedisplay();
      break;
    case 'v': // vermelho
      cor[0] = 1.0; cor[1] = 0.0; cor[2] = 0.0;
      glutPostRedisplay();
      break;
    case 27:
      exit(0);
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(256, 256);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Quadrado Interativo");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
