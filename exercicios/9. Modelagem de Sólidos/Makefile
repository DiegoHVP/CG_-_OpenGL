# Compila programas do curso de OpenGL
# digite: make programa.c
#

CC = g++
CFLAGS = -O2

##### MACROS #####

GL_LIBS = -lglut -lGLU -lGL -lm -lpng


##### RULES #####

.SUFFIXES:
.SUFFIXES: .c .cpp

.c:
	$(CC) $(CFLAGS) $< -o $@ $(GL_LIBS)

##### TARGETS ######

clean:
	-rm *.o *~