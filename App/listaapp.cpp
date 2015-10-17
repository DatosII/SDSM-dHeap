#include "listaapp.h"

ListaApp::ListaApp(){
    this->_head=NULL;
    this->_tail=NULL;
}

void ListaApp::insertData(NodoApp *pNodo){
    if (_head == 0){
        _head = _tail = pNodo;
    }

    else{
        NodoApp *tmp = _head;
        while((*tmp).getNext() != 0){
            tmp = tmp->getNext();
        }
        tmp->setNext(pNodo);
        _tail = tmp;
    }
}

bool ListaApp::deleteData(){

}
