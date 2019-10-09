MF=	Makefile

#COMPILER
CC=	gcc

CFLAGS=	-g
LFLAGS=	-lm

EXE=	percolate

SRC= \
		arralloc.c	\
		percolate.c	\
		uni.c
		

INC= \
		arralloc.h	\
		percolate.h	\
		uni.h

.SUFFIXES:
.SUFFIXES: .c .o

OBJ=	$(SRC:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $<

all:	$(EXE)

$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF) $(INC)

clean:
		rm -f $(OBJ) $(EXE) core