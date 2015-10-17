#include "nodoapp.h"

NodoApp::NodoApp(dObject *pDObject){
    this->_data=pDObject;
    this->_next = NULL;
    this->_id=pDObject->getID();
}

void NodoApp::setNext(NodoApp *pNext){
    this->_next=pNext;
}

NodoApp* NodoApp::getNext(){
    return this->_next;
}

unsigned int NodoApp::getId(){
    return _id;
}

