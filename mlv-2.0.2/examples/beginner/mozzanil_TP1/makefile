CC=gcc
CFLAGS=-Wall -ansi -pedantic
LDFLAGS=-lMLV
EXEC=TP1
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

TP1: TP1.o
	$(CC) $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
