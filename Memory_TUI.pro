TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp\
            ../Memory_API/board.cpp\
            ../Memory_API/player.cpp \
    ../Memory_API/card.cpp

LIBS += -L/usr/include/ncurses.h -lncurses
