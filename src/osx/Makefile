CC=clang
OPTS=-I../../include
OSX_OPTS=-F/System/Library/Frameworks -framework Foundation -framework QTKit

all:
	$(CC) $(OPTS) -c -fPIC QTKitCapture.m -o QTKitCapture.o
	$(CC) $(OSX_OPTS) -dynamiclib ../core/core.o QTKitCapture.o -o libopencapture.dylib
	$(CC) $(OSX_OPTS) ../core/cli.o ../core/core.o QTKitCapture.o -o opencapture
	make -C test

clean:
	rm *.o
	rm *.dylib
	rm opencapture
