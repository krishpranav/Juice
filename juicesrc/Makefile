CC = gcc

CFLAGS = -O0 -std=c11

all: repl juice api

.PHONY: repl juice api

repl: repl.c ../juice.c
	$(CC) $(CFLAGS) -DJUICE_REPL_MAIN -I.. -o $@ repl.c ../juice.c -lm

juice: juice.c ../juice.c
	$(CC) $(CFLAGS) -I.. -o $@ juice.c ../juice.c -lm
	
api: api.c ../juice.c
	$(CC) $(CFLAGS) -I.. -o $@ api.c ../juice.c -lm

clean:
	rm -f repl juice api *.o *.dSYM