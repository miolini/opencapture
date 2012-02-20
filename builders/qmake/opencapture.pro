QT -= core gui

INCLUDEPATH += ../../include

SOURCES += ../../src/core/core.c


mac {
	QMAKE_LFLAGS += -F/System/Library/Frameworks
	HEADERS += ../../src/osx/osx.h
	OBJECTIVE_SOURCES += ../../src/osx/osx.m
	LIBS += -framework Foundation -framework QTKit
}

linux {
	HEADERS += ../../src/linux/linux.h
	SOURCES += ../../src/linux/linux.c
}

cli {
	TEMPLATE = app
	SOURCES += ../../src/core/cli.c
	HEADERS += ../../src/core/cli.h
}

sharedlib {
	TEMPLATE = lib
}

staticlib {
	TEMPLATE = lib
	CONFiG += staticlib
}