
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[30]={
  0.0,  30.0, 30.0,  20.0, 30.0, 30.0,  30.0, 20.0, 30.0,
  30.0,  0.0, 30.0,   0.0,  0.0, 30.0,   0.0, 30.0,  0.0,
  30.0, 30.0,  0.0,  30.0,  0.0,  0.0,   0.0,  0.0,  0.0,
  30.0, 30.0, 20.0
};

static GLubyte frenteIndices[]    = {0, 4, 3, 2, 1};
static GLubyte trasIndices[]      = {5, 6, 7, 8};
static GLubyte esquerdaIndices[]  = {0, 5, 8, 4};
static GLubyte direitaIndices[]   = {2, 3, 7, 6, 9};
static GLubyte topoIndices[]      = {0, 1, 9, 6, 5};
static GLubyte fundoIndices[]     = {3, 4, 8, 7};
static GLubyte trianguloIndices[] = {1, 2, 9};

static int eixoy, eixox;
int largura, altura;
char face_atual = 'a'; // 'a' = all, 'f'=fundo, 't'=topo, 'e'=esquerda, 'd'=direita, 'F'=frente, 'T'=traseira, 'c'=canto

void desenhaFace(GLubyte* indices, int n, float r, float g, float b) {
  glColor3f(r, g, b);
  glBegin(GL_POLYGON);
  for (int i = 0; i < n; i++)
    glVertex3fv(&vertices[indices[i]*3]);
  glEnd();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef((GLfloat)eixoy, 1.0, 0.0, 0.0);
  glRotatef((GLfloat)eixox, 0.0, 1.0, 0.0);

  switch(face_atual) {
    case 'f': desenhaFace(fundoIndices, 4, LARANJA); break;
    case 't': desenhaFace(topoIndices, 5, AZUL); break;
    case 'F': desenhaFace(frenteIndices, 5, VERMELHO); break;
    case 'T': desenhaFace(trasIndices, 4, AMARELO); break;
    case 'e': desenhaFace(esquerdaIndices, 4, VERDE); break;
    case 'd': desenhaFace(direitaIndices, 5, CYAN); break;
    case 'c': desenhaFace(trianguloIndices, 3, ROSEO); break;
    default:
      desenhaFace(frenteIndices, 5, VERMELHO);
      desenhaFace(trasIndices, 4, AMARELO);
      desenhaFace(esquerdaIndices, 4, VERDE);
      desenhaFace(direitaIndices, 5, CYAN);
      desenhaFace(topoIndices, 5, AZUL);
      desenhaFace(fundoIndices, 4, LARANJA);
      desenhaFace(trianguloIndices, 3, ROSEO);
      break;
  }

  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  largura = w; altura = h;
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(45.0, 45.0, 100.0, 15.0, 15.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: exit(0); break;
    case 't': face_atual = 't'; break;
    case 'f': face_atual = 'f'; break;
    case 'F': face_atual = 'F'; break;
    case 'T': face_atual = 'T'; break;
    case 'e': face_atual = 'e'; break;
    case 'd': face_atual = 'd'; break;
    case 'c': face_atual = 'c'; break;
    case 'a': face_atual = 'a'; break;
    default: break;
  }
  glutPostRedisplay();
}

void init(void) {
  glClearColor(CINZA, 1.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(300, 300);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Tipos de Projeções");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
