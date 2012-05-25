QT -= core gui
СONFIG += cli

INCLUDEPATH += ../../include

SOURCES += ../../src/core/core.c

TEMPLATE = app
SOURCES += ../../src/core/cli.c
HEADERS += ../../src/core/cli.h

mac {
	QMAKE_LFLAGS += -F/System/Library/Frameworks
	HEADERS += ../../src/osx/osx.h
	OBJECTIVE_SOURCES += ../../src/osx/osx.m ../../src/osx/monitor.m
	LIBS += -framework Foundation -framework QTKit -framework CoreVideo -framework Cocoa
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
	TEMPLATE = lib
	SOURCES -= ../../src/core/cli.c
	HEADERS -= ../../src/core/cli.h
}

staticlib {
	TEMPLATE = lib
	CONFiG += staticlib
	SOURCES -= ../../src/core/cli.c
	HEADERS -= ../../src/core/cli.h
}