CC=clang

all:
	$(CC) -I../../../include -c -fPIC main.c -o main.o
	cp ../libopencapture.dylib ./
	$(CC) -L./ -lopencapture main.o -o opencapture_test

clean:
	rm -Rf *.o