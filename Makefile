CC=clang

all:
	@echo Please choose OS destination:
	@echo '$$ make <win32|linux|osx>'

core:
	make -C src/core

osx: core
	make -C src/osx

clean_core: 
	make -C src/core clean

clean_osx: clean_core
	make -C src/osx clean

linux: core
	make -C src/linux
	
clean_linux: core
	make -C src/linux clean