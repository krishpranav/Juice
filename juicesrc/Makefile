CC = gcc

CFLAGS = -O0 -std=c11

all: repl juice api

.PHONY: repl juice api

repl: repl.c juicesrc.c
	$(CC) $(CFLAGS) -DJUICE_REPL_MAIN -I.. -o $@ repl.c juicesrc.c -lm

juice: juice.c juicesrc.c
	$(CC) $(CFLAGS) -I.. -o $@ juice.c juicesrc.c -lm
	
api: api.c juicesrc.c
	$(CC) $(CFLAGS) -I.. -o $@ api.c juicesrc.c -lm

clean:
	rm -f repl juice api *.o *.dSYM