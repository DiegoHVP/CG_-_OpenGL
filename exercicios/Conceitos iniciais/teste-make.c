#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void display(void);
void timer(int);
void keyboard(unsigned char key, int x, int y);

/* cores do quadrado */
GLfloat r = 0.5, g = 0.5, b = 0.5;

#define CLAMP(val, min, max) ((val < min) ? min : (val > max) ? max : val)

float random_step(float step_size) {
  return ((float)rand() / RAND_MAX) * 2.0f * step_size - step_size;
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(256, 256);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  // inicia um temporizador. após 33ms ativa a funcao timer
  glutTimerFunc(10, timer, 1);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
  glOrtho(0, 1, 0, 1, -1, 1);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void timer(int value) {
  r = CLAMP(r + random_step(0.05), 0.0f, 1.0f);
  g = CLAMP(g + random_step(0.05), 0.0f, 1.0f);
  b = CLAMP(b + random_step(0.05), 0.0f, 1.0f);
  //  printf("r: %f g: %f b: %f\n", r, g, b);
  glutPostRedisplay();
  glutTimerFunc(33, timer, 1);
}

void display(void) {
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(r, g, b);
  glBegin(GL_POLYGON);
  glVertex2f(0.25, 0.25);
  glVertex2f(0.75, 0.25);
  glVertex2f(0.75, 0.75);
  glVertex2f(0.25, 0.75);
  glEnd();
  glFlush();
}