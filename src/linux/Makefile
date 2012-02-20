CC=clang
OPTS=-I../../include
OSX_OPTS=

all:
	$(CC) $(OPTS) -c -fPIC linux.c -o linux.o
	$(CC) $(OSX_OPTS) -shared ../core/core.o linux.o -o libopencapture.so
	ar rcs opencapture.a ../core/core.o linux.o
	$(CC) $(OSX_OPTS) ../core/cli.o ../core/core.o linux.o -o opencapture

clean:
	rm *.o
	rm *.so
	rm opencapture
