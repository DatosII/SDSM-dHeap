#include "nodoapp.h"

NodoApp::NodoApp(){
    this->next = 0;
    //this->data=NULL;
}

void NodoApp::setNext(NodoApp *pNext){
    this->next=pNext;
}

dObject NodoApp::getNext(){
    return this->data;
}

