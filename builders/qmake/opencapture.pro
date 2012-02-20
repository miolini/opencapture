QT -= core gui
СONFIG = cli

INCLUDEPATH += ../../include

SOURCES += ../../src/core/core.c


mac {
	QMAKE_LFLAGS += -F/System/Library/Frameworks
	HEADERS += ../../src/osx/osx.h
	OBJECTIVE_SOURCES += ../../src/osx/osx.m
	LIBS += -framework Foundation -framework QTKit
	CONFIG -= app_bundle
}

unix:!macx {
	HEADERS += ../../src/linux/linux.h
	SOURCES += ../../src/linux/linux.c
}

win32 {
	HEADERS += ../../src/win32/win32.h
	SOURCES += ../../src/win32/win32.c
}

sharedlib {
	CONFIG -= cli
	TEMPLATE = lib
}

staticlib {
	CONFIG -= cli
	TEMPLATE = lib
	CONFiG += staticlib
}

cli {
	TEMPLATE = app
	SOURCES += ../../src/core/cli.c
	HEADERS += ../../src/core/cli.h
}
