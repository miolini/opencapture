CC=clang
OPTS=-I../../include
LINUX_OPTS=-O3

all:
	$(CC) $(OPTS) -c -fPIC linux.c -o linux.o
	$(CC) $(LINUX_OPTS) -shared ../core/core.o linux.o -o libopencapture.so
	ar rcs opencapture.a ../core/core.o linux.o
	$(CC) $(LINUX_OPTS) ../core/cli.o ../core/core.o linux.o -o opencapture

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.a
	rm -f opencapture
