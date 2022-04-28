CC=g++
CFLAGS=-I ../include
DEPS=Graph.h USFApprox.h

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

hellomake: main.o Graph.o USFApprox.o
		$(CC) -o hellomake main.o Graph.o USFApprox.o


