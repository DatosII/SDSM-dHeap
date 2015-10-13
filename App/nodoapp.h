#ifndef NODOAPP_H
#define NODOAPP_H

#include "Object/dobject.h"

class NodoApp
{
private:
    dObject data;
      NodoApp *next;

public:
    NodoApp();

    void setNext(NodoApp *pNext);
    dObject getNext();



};

#endif // NODOAPP_H
