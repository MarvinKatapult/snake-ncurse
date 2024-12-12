
CC=gcc
CFLAGS=-Wextra -Wall -pedantic -g -I./
BIN=snake

all:
	$(CC) -o $(BIN) $(CFLAGS) *.c -lncurses 

clean:
	rm $(BIN)
