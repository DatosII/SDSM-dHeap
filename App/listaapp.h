#ifndef LISTAAPP_H
#define LISTAAPP_H
#include "App/nodoapp.h"

class ListaApp
{
private:
    NodoApp* _head;
    NodoApp* _tail;
public:
    ListaApp();
    void insertData(dObject pData);
    void deleteData();
};

#endif // LISTAAPP_H
