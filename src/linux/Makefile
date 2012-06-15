CC=clang
OPTS=-I../../include
LINUX_OPTS=-Os

all:
	$(CC) $(OPTS) -c -D_LINUX_DEV -fPIC linux.c -o linux.o
	$(CC) $(LINUX_OPTS) -shared ../core/core.o linux.o -o libopencapture.so
	ar rcs opencapture.a ../core/core.o linux.o
	$(CC) $(LINUX_OPTS) ../cli/cli.o ../core/core.o linux.o -o opencapture

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.a
	rm -f opencapture
