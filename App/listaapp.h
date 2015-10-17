#ifndef LISTAAPP_H
#define LISTAAPP_H

#include "App/nodoapp.h"

/**
 * @brief The ListaApp class
 */
class ListaApp
{
private:
    NodoApp* _head;
    NodoApp* _tail;
public:
    ListaApp();
    ~ListaApp();
    void insertData(NodoApp *pNodo);
    void remove(unsigned int pID);
    void format();
    NodoApp* find(unsigned int pData);
};

#endif // LISTAAPP_H
