CC=clang
OPTS=-I../../include
OSX_OPTS=-F/System/Library/Frameworks -framework Foundation -framework QTKit -framework CoreVideo

all: common

common:
	$(CC) $(OPTS) -c -fPIC osx.m -o osx.o
	$(CC) $(OSX_OPTS) -dynamiclib ../core/core.o osx.o -o libopencapture.dylib
	ar rcs opencapture.a ../core/core.o osx.o
	$(CC) $(OSX_OPTS) ../core/cli.o ../core/core.o osx.o -o opencapture

	

test: common
	$(CC) -I/opt/local/include $(OPTS) -c -fPIC test.c -o test.o
	$(CC) $(OSX_OPTS) -L/opt/local/lib -ljpeg opencapture.a test.o -o opencapture_test


clean:
	rm *.o
	rm *.a
	rm *.dylib
	rm opencapture 
	rm opencapture_test
