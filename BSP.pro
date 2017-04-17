TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra

LIBS           += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += main.cc \
    Frame.cc \
    Dungeon.cc

HEADERS += \
    Frame.h \
    Dungeon.h

