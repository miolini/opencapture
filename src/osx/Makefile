CC=clang
OPTS=-I../../include
OSX_OPTS=-F/System/Library/Frameworks -framework Foundation -framework QTKit

all:
	$(CC) $(OPTS) -c -fPIC osx.m -o osx.o
	$(CC) $(OSX_OPTS) -dynamiclib ../core/core.o osx.o -o libopencapture.dylib
	ar rcs opencapture.a ../core/core.o osx.o
	$(CC) $(OSX_OPTS) ../core/cli.o ../core/core.o osx.o -o opencapture
	make -C test

clean:
	rm *.o
	rm *.a
	rm *.dylib
	rm opencapture
