// Visualizador de espectro de MP3 com SDL2, FFTW e OpenGL (ajuste de logscale e
// balanceamento de bandas)

#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <fftw3.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// === PARÂMETROS === //
constexpr int SAMPLE_RATE = 44100;
constexpr int CHANNELS = 2;
constexpr int FFT_SIZE = 512;
constexpr int BANDS = 64;
constexpr float DB_RANGE = 40.0f;
constexpr float SPECTRUM_MULTIPLIER = 1e-2f;

// === BUFFERS === //
double* fftIn;
fftw_complex* fftOut;
fftw_plan fftPlan;
std::vector<float> window(FFT_SIZE);
std::vector<float> logscale(BANDS + 1);
std::vector<float> spectrum(BANDS);
std::vector<float> maxspectrum(BANDS);

// === FUNÇÕES AUXILIARES === //
inline float CLAMP(float val, float minv, float maxv) {
  return std::max(minv, std::min(maxv, val));
}

void initWindowAndScale() {
  for (int i = 0; i < FFT_SIZE; ++i)
    window[i] = 0.5f * (1 - cos(2 * M_PI * i / (FFT_SIZE - 1)));

  // Distribuição logarítmica corrigida
  float minLog = log10f(1.0f);
  float maxLog = log10f(FFT_SIZE / 2.0f);
  for (int i = 0; i <= BANDS; ++i) {
    float logIndex = pow(10.0f, minLog + (maxLog - minLog) * i / BANDS) - 1.0f;
    logscale[i] = CLAMP(logIndex, 0.0f, FFT_SIZE / 2.0f - 1.0f);
  }
}

// === CALLBACK DE ÁUDIO === //
void audioCallback(void* udata, Uint8* stream, int len) {
  spectrum;  // Armazena o espectro anterior

  if (!stream || len < FFT_SIZE * CHANNELS * (int)sizeof(Sint16)) return;

  Sint16* samples = reinterpret_cast<Sint16*>(stream);
  for (int i = 0; i < FFT_SIZE; ++i) {
    float l = samples[2 * i] / 32768.0f;
    float r = samples[2 * i + 1] / 32768.0f;
    float mono = (l + r) * 0.5f;
    fftIn[i] = mono * window[i];
  }

  fftw_execute(fftPlan);

  std::vector<float> magnitudes(FFT_SIZE / 2);
  for (int i = 0; i < FFT_SIZE / 2; ++i) {
    float re = fftOut[i][0];
    float im = fftOut[i][1];
    float amplitude = SPECTRUM_MULTIPLIER * sqrtf(re * re + im * im);
    magnitudes[i] = CLAMP(amplitude, 0.0f, 1.0f);
  }

  for (int i = 0; i < BANDS; ++i) {
    int a = ceilf(logscale[i]);
    int b = floorf(logscale[i + 1]);
    float sum = 0;

    if (b < a) {
      sum += magnitudes[b] * (logscale[i + 1] - logscale[i]);
    } else {
      if (a > 0) sum += magnitudes[a - 1] * (a - logscale[i]);
      for (int j = a; j < b; ++j) sum += magnitudes[j];
      if (b < FFT_SIZE / 2) sum += magnitudes[b] * (logscale[i + 1] - b);
    }

    sum *= FFT_SIZE / 24.0f;
    float dB = 20.0f * log10f(sum + 1e-6f);
    float val = 1.0f + dB / DB_RANGE;
    spectrum[i] = CLAMP(val, 0.0f, 1.0f);
    spectrum[i] = val;
  }
  // normalize spectrum to [0, 1]
  float minVal = *std::min_element(spectrum.begin(), spectrum.begin() + BANDS);
  // std::cout << "Min: " << minVal << std::endl;
  if (minVal < 0.0f) {
    for (int i = 0; i < BANDS; ++i) {
      spectrum[i] -= minVal;  // Ajusta para que o mínimo seja 0
    }
  }
  float maxVal = *std::max_element(spectrum.begin(), spectrum.begin() + BANDS);
  // std::cout << "Max: " << maxVal << std::endl;
  //  Normaliza o espectro para o intervalo [0, 1]
  //  Isso garante que o espectro esteja sempre entre 0 e 1
  //  mesmo que o valor máximo seja negativo ou zero
  //  Isso é importante para evitar problemas de visualização
  //  quando o espectro é muito baixo ou negativo
  //  e para garantir que o espectro seja sempre visível
  //  e para garantir que o espectro seja sempre visível
  if (maxVal > 0.0f) {
    for (int i = 0; i < BANDS; ++i) {
      spectrum[i] /= maxVal;
    }
  }

  glutPostRedisplay();
}

// === OPENGL === //
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();


  float raio_base = 0.5f; // raio fixo do círculo
  float cx = 0.0f, cy = 0.0f; // centro do círculo

  // Desenha o círculo central
  glColor3f(0.3, 0.3, 0.3);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 100; ++i) {
    float ang = 2.0f * M_PI * i / 100;
    float x = raio_base * cos(ang);
    float y = raio_base * sin(ang);
    glVertex2f(x, y);
  }
  glEnd();

  // Desenha os triângulos do espectro
  for (int i = 0; i < BANDS; ++i) {
    // Intensidade da frequência
    float h = maxspectrum[i];
    if (h < 0.01f) continue; // Ignora bandas com baixa intensidade
    // Ângulo do triângulo
    // Distribuição uniforme ao longo do círculo
    // Cada triângulo ocupa uma fração do círculo
    float ang = 2.0f * M_PI * i / BANDS;

    // Direção radial
    // dx e dy são as componentes x e y da direção radial
    float dx = cos(ang);
    float dy = sin(ang);

    // Base do triângulo: dois pontos na borda do círculo
    // angL e angR são os ângulos da base do triângulo
    // delta é a largura da base do triângulo
    float delta = (2 * M_PI) / BANDS / 2;
    float angL = ang - delta;
    float angR = ang + delta;

    // Calcula as coordenadas dos pontos da base do triângulo
    // xL e yL são as coordenadas do ponto esquerdo da base
    // xR e yR são as coordenadas do ponto direito da base    
    float xL = cx + raio_base * cos(angL);
    float yL = cy + raio_base * sin(angL);
    float xR = cx + raio_base * cos(angR);
    float yR = cy + raio_base * sin(angR);

    // Ponta do triângulo: fora do círculo
    // xP e yP são as coordenadas da ponta do triângulo
    // A ponta é deslocada para fora do círculo na direção radial
    // raio_base + h é o raio do círculo aumentado pela altura do triângulo
    float xP = cx + (raio_base + h) * dx;
    float yP = cy + (raio_base + h) * dy;

    // Cor suave
    float r = 0.5f + 0.5f * sin(ang);
    float g = 0.5f + 0.5f * sin(ang + M_PI / 3.0f);
    float b = 0.5f + 0.5f * sin(ang + 2 * M_PI / 3.0f);
    glColor3f(r, g, b);

    // Triângulo
    glBegin(GL_TRIANGLES);
      glVertex2f(xL, yL); // base esquerda (borda do círculo)
      glVertex2f(xR, yR); // base direita (borda do círculo)
      glVertex2f(xP, yP); // ponta (para fora)
    glEnd();
  }

  glutSwapBuffers();
}



void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Janela de -1 a +1, proporcional à janela
    float aspect = (float)w / (float)h;
    if (aspect >= 1.0f)
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    else
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void idle() {
  float decay = 0.01f;  // Decaimento do espectro
  // Função de callback ociosa, não faz nada
  // Pode ser usada para atualizar a tela ou processar eventos
  // Pode ser usada para atualizar a tela ou processar eventos
  std::transform(spectrum.begin(), spectrum.end(), maxspectrum.begin(),
                 maxspectrum.begin(), [](float a, float b) {
                   float decay = 0.02f;  // Decaimento do espectro
                   return std::max(a, b) - decay;
                 });

  glutPostRedisplay();
}

void initGL() {
  glClearColor(0, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}

// === MAIN === //
int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <arquivo.mp3>" << std::endl;
    return 1;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 400);
  glutCreateWindow("Visualizador de Espectro");
  initGL();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(
      [](unsigned char key, int x, int y) {  // Função de callback de teclado
        if (key == 27) {                     // Tecla ESC
          exit(0);                           // Sai do loop principal do GLUT
        }
      });

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cerr << "Erro SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (Mix_OpenAudio(SAMPLE_RATE, MIX_DEFAULT_FORMAT, CHANNELS, 4096) < 0) {
    std::cerr << "Erro Mix_OpenAudio: " << Mix_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  fftIn = (double*)fftw_malloc(sizeof(double) * FFT_SIZE);
  fftOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
  fftPlan = fftw_plan_dft_r2c_1d(FFT_SIZE, fftIn, fftOut, FFTW_ESTIMATE);
  initWindowAndScale();
  Mix_SetPostMix(audioCallback, nullptr);

  Mix_Music* music = Mix_LoadMUS(argv[1]);
  if (!music) {
    std::cerr << "Erro Mix_LoadMUS: " << Mix_GetError() << std::endl;
    return 1;
  }
  Mix_PlayMusic(music, -1);

  glutMainLoop();

  fftw_destroy_plan(fftPlan);
  fftw_free(fftIn);
  fftw_free(fftOut);
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}
