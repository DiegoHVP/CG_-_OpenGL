/* braco-garra-3d.c - Versao 3D, solida e colorida do braco com garra. */
#include <GL/glut.h>
#include <stdlib.h>

/* Variaveis de estado para os angulos de rotacao */
static int shoulder = 0, elbow = 0;
static int polegar = 0, indicador = 0, Medio = 0;
static int base_rotation_y = 0;

void init(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
   glEnable(GL_CULL_FACE);  // Habilita o descarte de faces traseiras
}

// tag::display[]
void display(void) {
   // Limpa os buffers de cor e profundidade
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();

   // Rotaciona a base em torno do eixo Y
   glRotatef((GLfloat) base_rotation_y, 0.0, 1.0, 0.0);


   // Move para o topo da base para desenhar o ombro
   glTranslatef(0.0, 0.25, 0.0);

   /* Ombro */
   glColor3f(0.0, 1.0, 0.0); // Verde
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();

   /* Cotovelo */
   glColor3f(0.0, 0.0, 1.0); // Azul
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();

   /* ---- INICIO DA GARRA ---- */
   glTranslatef(1.0, 0.0, 0.0);

   /* Palma */
   glColor3f(1.0, 1.0, 0.0); // Amarelo
   glPushMatrix();
   glScalef(0.5, 0.5, 1.0);
   glutSolidCube(1.0);
   glPopMatrix();

   /* Dedo Indicador */
   glColor3f(0.0, 1.0, 1.0); // Ciano
   glPushMatrix();
   glTranslatef(0.0, 0.35, 0.0);
   glRotatef((GLfloat) indicador, 0.0, 0.0, 1.0);
   glTranslatef(0.3, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.6, 0.15, 0.2);
   glutSolidCube(1.0);
   glPopMatrix();
   glPopMatrix();

   /* Dedo Medio */
   glColor3f(1.0, 0.0, 1.0); // Magenta
   glPushMatrix();
   glTranslatef(0.0, 0.35, 0.5);
   glRotatef((GLfloat) Medio, 0.0, 0.0, 1.0);
   glTranslatef(0.3, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.6, 0.15, 0.2);
   glutSolidCube(1.0);
   glPopMatrix();
   glPopMatrix();

   /* Dedo Polegar */
   glColor3f(1.0, 1.0, 1.0); // Branco
   glPushMatrix();
   glTranslatef(0.0, -0.35, 0.0);
   glRotatef((GLfloat) polegar, 0.0, 0.0, 1.0);
   glTranslatef(0.3, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.6, 0.15, 0.2);
   glutSolidCube(1.0);
   glPopMatrix();
   glPopMatrix();
   /* ---- FIM DA GARRA ---- */

   glPopMatrix();
   glutSwapBuffers(); // Troca os buffers (traseiro com o frontal)
}
// end::display[]

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -8.0); // Afasta a camera para ver melhor o modelo
}

// tag::btn[]
void keyboard (unsigned char key, int x, int y) {
   switch (key) {
      case 'b': base_rotation_y = (base_rotation_y + 5) % 360; glutPostRedisplay(); break;
      case 'B': base_rotation_y = (base_rotation_y - 5) % 360; glutPostRedisplay(); break;
      case 's': shoulder = (shoulder + 5) % 360; glutPostRedisplay(); break;
      case 'S': shoulder = (shoulder - 5) % 360; glutPostRedisplay(); break;
      case 'e': elbow = (elbow + 5) % 360; glutPostRedisplay(); break;
      case 'E': elbow = (elbow - 5) % 360; glutPostRedisplay(); break;
      case 'i': indicador = (indicador + 5) % 360; glutPostRedisplay(); break;
      case 'I': indicador = (indicador - 5) % 360; glutPostRedisplay(); break;
      case 'm': Medio = (Medio + 5) % 360; glutPostRedisplay(); break;
      case 'M': Medio = (Medio - 5) % 360; glutPostRedisplay(); break;
      case 'p': polegar = (polegar + 5) % 360; glutPostRedisplay(); break;
      case 'P': polegar = (polegar - 5) % 360; glutPostRedisplay(); break;
      case 27: exit(0); break;
      default: break;
   }
}
// end::btn[]

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   // Habilita buffer duplo, modo RGB e buffer de profundidade
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow(argv[0]);

   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}