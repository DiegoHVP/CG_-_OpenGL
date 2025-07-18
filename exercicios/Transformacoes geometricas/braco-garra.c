#include <GL/glut.h>
#include <stdlib.h>

/* Variaveis de estado para os angulos de rotacao */
// Variaveis para a garra
// shoulder e usad para o ombro
// elbow para o cotovelo

// polegar, indicador e Medio para os dedos
static int shoulder = 0, elbow = 0;
static int polegar = 0, indicador = 0, Medio = 0;

void init(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void) {
   glClear (GL_COLOR_BUFFER_BIT);
   glPushMatrix();

   /* Ombro */
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   /* Cotovelo */
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();


   // tag::dedos[]
   /* ---- INICIO DA GARRA ---- */
   // Move para a ponta do antebraco para desenhar a garra
   glTranslatef(1.0, 0.0, 0.0);

   /* Palma */
   glPushMatrix();
   glScalef(0.5, 0.5, 1.0);
   glutWireCube(1.0);
   glPopMatrix();

   /* Dedo Indicador */
   glPushMatrix();
   glTranslatef(0.0, 0.35, 0.0); // Posiciona o dedo na parte superior da palma
   glRotatef((GLfloat) indicador, 0.0, 0.0, 1.0);
   glTranslatef(0.3, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.6, 0.15, 0.2);
   glutWireCube(1.0);
   glPopMatrix();
   glPopMatrix();

   /* Dedo Medio */
   glPushMatrix();
   glTranslatef(0.0, 0.35, 0.5); // Posiciona o dedo na parte superior e 'frente' da palma
   glRotatef((GLfloat) Medio, 0.0, 0.0, 1.0);
   glTranslatef(0.3, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.6, 0.15, 0.2);
   glutWireCube(1.0);
   glPopMatrix();
   glPopMatrix();

   /* Dedo Polegar */
   glPushMatrix();
   glTranslatef(0.0, -0.35, 0.0); // Posiciona o dedo na parte inferior da palma
   glRotatef((GLfloat) polegar, 0.0, 0.0, 1.0);
   glTranslatef(0.3, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.6, 0.15, 0.2);
   glutWireCube(1.0);
   glPopMatrix();
   glPopMatrix();
   /* ---- FIM DA GARRA ---- */
   // end::dedos[]

   glPopMatrix();
   glFlush();
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);
}

// tag::btn[]
void keyboard (unsigned char key, int x, int y) {
   // controla os angulos de rotacao
   // usando as teclas s/S para o ombro, e e/E para o cotovelo
   // i/I, m/M e p/P para os dedos indicador, medio e polegar
   // 27 para sair do programa
    switch (key) {
    
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}