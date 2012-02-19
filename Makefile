CC=llvm-gcc

all:
	$(CC) -c -fPIC src/opencapture.c -o src/opencapture.o
	$(CC) -shared src/opencapture.o -o src/opencapture.dylib

clean:
	rm -Rf src/*.o src/opencapture.dylib