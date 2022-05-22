CC=gcc
CFLAGS=-Wall -ansi -pedantic
LDFLAGS=-lMLV
EXEC=game
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

game: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: grid.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
