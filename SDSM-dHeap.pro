#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T14:22:23
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SDSM-dHeap
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Heap/dheap.cpp \
    Listas/linkedlist.cpp \
    Listas/linkedlistmd.cpp \
    Nodos/node_ll.cpp \
    Nodos/node_md.cpp \
    Pointer/d_pointer_size_type.cpp \
    Object/dobject.cpp \
    Object/dint.cpp \
    Object/dchar.cpp \
    Object/dfloat.cpp \
    Object/dstring.cpp \
    App/App.cpp \
    App/listaapp.cpp \
    App/nodoapp.cpp

LIBS += -pthread

CONFIG += c++11

HEADERS += \
    Heap/dheap.h \
    Listas/linkedlist.h \
    Listas/linkedlistmd.h \
    Nodos/node_ll.h \
    Nodos/node_md.h \
    Pointer/d_pointer_size_type.h \
    Object/dobject.h \
    Object/dint.h \
    Object/dchar.h \
    Object/dfloat.h \
    Object/dstring.h \
    App/App.h \
    App/listaapp.h \
    App/nodoapp.h

DISTFILES +=
