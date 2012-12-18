TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp\
            ../Memory_API/board.cpp\
            ../Memory_API/card.cpp\
            ../Memory_API/player.cpp \
    game.cpp \
    players_array.cpp

LIBS += -L/usr/include/ncurses.h -lncurses

HEADERS += \
    game.h \
    players_array.h
