#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // para usar usleep()
#include <math.h>

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

static int eixoy = 0, eixox = 0;
int largura, altura;
char face_atual = 'a'; // 'a' = all

int perspectiva = 1;
int sentidoX = 1, sentidoY = 1;

void idle(void) {
    // Incremento dos eixos
    eixox += sentidoX;
    eixoy += sentidoY;

    // Mantém eixos entre 0 e 360
    if (eixox >= 360) sentidoX = -1;
    if (eixox <= 0) sentidoX = 1;
    if (eixoy >= 360) sentidoY = -1;
    if (eixoy <= 0) sentidoY = 1;

    usleep(30000); // 30ms
    glutPostRedisplay();
}

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
  glTranslatef(-15.0, -15.0, -15.0);
  glRotatef((GLfloat)eixoy, 1.0, 0.0, 0.0);
  glRotatef((GLfloat)eixox, 0.0, 1.0, 0.0);
  glTranslatef(15.0, 15.0, 15.0);

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
    largura = w;
    altura = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspectiva)
        gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 200.0);
    else
        glOrtho(0.0, 60.0, 0.0, 60.0, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (perspectiva)
        gluLookAt(60, 60, 100, 15, 15, 15, 0, 1, 0);
    else
        glTranslatef(-30.0, -30.0, -100.0);
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
    case 'p': perspectiva = 1; reshape(largura, altura); break;
    case 'o': perspectiva = 0; reshape(largura, altura); break;
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
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
