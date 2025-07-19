
#include <GL/glut.h>
#include <stdlib.h>

float corFundo[4][3];  // cores de fundo dos polígonos
float corBorda[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; // bordas pretas
int modo = 0; // 0 = fundo, 1 = borda

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0, 256, 0, 256, -1, 1);
    for(int i=0;i<4;i++) // inicializar todos amarelos
        corFundo[i][0] = corFundo[i][1] = 1.0, corFundo[i][2]=0.0;
}

void desenha(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<4;i++){
        // Desenhar polígonos com cores de fundo e borda
        glColor3fv(corFundo[i]);
        glBegin(GL_POLYGON);
        // Desenhar polígonos em posições diferentes
            switch(i){
                case 0: glVertex2i(10,10); glVertex2i(100,10); glVertex2i(100,100); glVertex2i(10,100); break;
                case 1: glVertex2i(120,10); glVertex2i(230,10); glVertex2i(230,100); glVertex2i(120,100); break;
                case 2: glVertex2i(10,120); glVertex2i(100,120); glVertex2i(100,230); glVertex2i(10,230); break;
                case 3: glVertex2i(120,120); glVertex2i(230,120); glVertex2i(230,230); glVertex2i(120,230); break;
            }
        glEnd();

        // Desenhar bordas dos polígonos
        glColor3fv(corBorda[i]);
        glBegin(GL_LINE_LOOP);
            switch(i){
                case 0: glVertex2i(10,10); glVertex2i(100,10); glVertex2i(100,100); glVertex2i(10,100); break;
                case 1: glVertex2i(120,10); glVertex2i(230,10); glVertex2i(230,100); glVertex2i(120,100); break;
                case 2: glVertex2i(10,120); glVertex2i(100,120); glVertex2i(100,230); glVertex2i(10,230); break;
                case 3: glVertex2i(120,120); glVertex2i(230,120); glVertex2i(230,230); glVertex2i(120,230); break;
            }
        glEnd();
    }
    // tag::buffer2[]
    glFlush();
    // end::buffer2[]
}

// tag::selecao[]
void keyboard(unsigned char key, int x, int y){
    // se 'b' pressionado, muda cor de fundo
    // se 'f' pressionado, muda cor de borda
    if(key=='b') modo=1;
    if(key=='f') modo=0;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    // se botão esquerdo pressionado
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        // converter coordenadas de mouse para coordenadas do OpenGL
        y=256-y;
        // verificar em qual polígono o mouse está
        for(int i=0;i<4;i++){
            int dentro=0;
            switch(i){
                case 0: if(x>=10 && x<=100 && y>=10 && y<=100) dentro=1; break;
                case 1: if(x>=120 && x<=230 && y>=10 && y<=100) dentro=1; break;
                case 2: if(x>=10 && x<=100 && y>=120 && y<=230) dentro=1; break;
                case 3: if(x>=120 && x<=230 && y>=120 && y<=230) dentro=1; break;
            }
            // se dentro do polígono, mudar cor
            if(dentro){
                // gerar cor aleatória de rgb
                float r=rand()/ (float) RAND_MAX;
                float g=rand()/ (float) RAND_MAX;
                float b=rand()/ (float) RAND_MAX;
                if(modo==0)
                    corFundo[i][0]=r, corFundo[i][1]=g, corFundo[i][2]=b;
                else
                    corBorda[i][0]=r, corBorda[i][1]=g, corBorda[i][2]=b;
            }
        }
    }
    // se botão direito pressionado, reiniciar cores
    glutPostRedisplay();
}
// end::selecao[]

int main(int argc, char** argv){
    glutInit(&argc, argv);
    
    // tag::buffer1[]
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // end::buffer1[]
    glutInitWindowSize(256,256);
    glutCreateWindow("Seleção de polígonos");
    init();
    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

