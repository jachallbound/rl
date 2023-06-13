CC=gcc
STDFLAGS=-std=c99
WFLAGS=-Wall -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Wextra
CFLAGS=-D_POSIX_C_SOURCE=199309L
LDFLAGS=-lm
PROGRAM=main
PFLAGS=-pg -g # Profiler flags
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: $(OBJ)
	$(CC) $(LDFLAGS) -o $(PROGRAM) $(OBJ)

%.o:%.c
	$(CC) $(WFLAGS) $(STDFLAGS) $(CFLAGS) -c $< $(PFLAGS)

clean:
	rm -fv *.o $(PROGRAM)