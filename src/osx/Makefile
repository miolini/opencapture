CC=clang

all:
	$(CC) -c -fPIC QTKitCapture.m -o QTKitCapture.o
	$(CC) -F/System/Library/Frameworks -framework Foundation ../cli.o QTKitCapture.o -o opencapture.o

clean:
	rm *.o
