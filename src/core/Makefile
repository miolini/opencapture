CC=clang
OPTS=-I../../include

all:
	$(CC) $(OPTS) -c -fPIC opencapture.c -o opencapture.o
	$(CC) $(OPTS) -c -fPIC cli.c -o cli.o

clean:
	rm *.o