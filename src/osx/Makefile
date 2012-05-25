CC=clang
OPTS=-I../../include
OSX_OPTS=-F/System/Library/Frameworks -framework Foundation -framework QTKit -framework CoreVideo -framework Cocoa

all: common

core:
	make -C ../core

common:
	$(CC) $(OPTS) -c -fPIC osx.m -o osx.o
	$(CC) $(OPTS) -c -fPIC monitor.m -o monitor.o
	$(CC) $(OSX_OPTS) -dynamiclib ../core/core.o osx.o -o libopencapture.dylib
	ar rcs opencapture.a ../core/core.o osx.o
	$(CC) $(OSX_OPTS) ../core/cli.o ../core/core.o osx.o monitor.o -o opencapture

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.dylib
	rm -f opencapture 
	rm -f .DS_Store
	rm -Rf frames
