CC=clang

all:
	$(CC) -c -fPIC cli.c -o cli.o
	make -C osx

clean:
	make -C osx clean
	rm *.o