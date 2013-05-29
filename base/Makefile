CC=gcc
CFLAGS=-g -Wall
LIBS=-lm
GL=-lglut -lGL -lGLU

all: mm-null mm-opengl

mm-visual.h: mm-base.h

mm-null.o: mm-null.c mm-base.h mm-visual.h
mm-opengl.o: mm-opengl.c mm-base.h mm-visual.h

mm.o: mm.c mm-base.h mm-visual.h

mm-null: mm.o mm-null.o
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}

mm-opengl: mm.o mm-opengl.o
	${CC} ${CFLAGS} -o $@ $^ ${LIBS} ${GL}

clean:
	rm -f *.o

fresh: clean all

