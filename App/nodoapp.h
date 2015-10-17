#ifndef NODOAPP_H
#define NODOAPP_H

#include "Object/dobject.h"

class NodoApp
{
private:
    dObject *_data;
    NodoApp *_next;
    unsigned int _id;

public:
    NodoApp(dObject *pDObject);
    void setNext(NodoApp *pNext);
    NodoApp *getNext();
    unsigned int getId();
    dObject* getData();




};

#endif // NODOAPP_H
