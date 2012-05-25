CC=clang
OPTS=-I../../include

all:
	$(CC) $(OPTS) -c -fPIC core.c -o core.o
	$(CC) $(OPTS) -c -fPIC cli.c -o cli.o

clean:
	rm -f *.o