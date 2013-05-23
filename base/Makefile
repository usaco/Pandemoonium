CC=gcc
CFLAGS=-g -Wall

GTKFLAGS=`pkg-config --cflags gtk+-2.0 gthread-2.0`
GTKLIBS=`pkg-config --cflags --libs gtk+-2.0 gthread-2.0`

all: mm-null

mm-visual.h: mm-base.h

mm-null.o: mm-null.c mm-base.h mm-visual.h
mm-opengl.o: mm-opengl.c mm-base.h mm-visual.h

mm.o: mm.c mm-base.h mm-visual.h

mm-null: mm.o mm-null.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f *.o

fresh: clean all

