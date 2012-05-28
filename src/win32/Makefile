CC=clang++
OPTS=-I../../include
win32_OPTS=

all:
	$(CC) $(OPTS) -c -fPIC win32.cpp -o win32.o
	$(CC) $(win32_OPTS) -shared ../core/core.o win32.o -o libopencapture.so
	ar rcs opencapture.a ../core/core.o win32.o
	$(CC) $(win32_OPTS) ../cli/cli.o ../core/core.o win32.o -o opencapture

clean:
	rm -f *.o
	rm -f *.dll
	rm -f *.a
	rm -f *.so
	rm -f opencapture
