CC=clang

all:
	$(CC) -I../../../include -c -fPIC main.c -o main.o
	$(CC) -F/System/Library/Frameworks -framework Foundation -framework QTKit ../opencapture.a main.o -o opencapture_test

clean:
	rm -Rf *.o
	rm *.dylib
	rm opencapture_test