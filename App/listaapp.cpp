#include "listaapp.h"

ListaApp::ListaApp(){
    this->_head=NULL;
    this->_tail=NULL;
}

ListaApp::~ListaApp(){
    if(_head != 0){
        NodoApp *current = _head;
        NodoApp *next;

        while(current->getNext() != 0){
            next = current->getNext();
            current->getData()->deleteData();
            delete current;
            current = next;
        }
    }
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



void  ListaApp::remove(unsigned int pID){
    if(_head == 0){ //Lista esta vacia
        return;
    }
    else if(_head->getId() == pID){ //Dato se encuentra en el head
        NodoApp *temp = _head;
        _head = _head->getNext();
        delete temp;
    }
    else{ //Dato no esta en el head, se debe buscar
        NodoApp *prev = _head, *next = _head->getNext();
        while(next != 0){
            if(next->getId() == pID){
                prev->setNext(next->getNext());

                if(next == _tail){
                    _tail = prev;
                }
                delete next;
                break;
            }

            prev = next;
            next = next->getNext();
        }
    }
}

void ListaApp::format(){
    if(_head != 0){
        NodoApp *current = _head;
        NodoApp *next;

        while(current != 0){
            next = current->getNext();
            current->getData()->deleteData();
            delete current;
            current = next;
        }
        _head = NULL;
    }
}




NodoApp* ListaApp::find(unsigned int pData){
        if(_head != 0){
            NodoApp *temp = _head;
            while(temp != 0){
                if(temp->getId() == pData){
                    return temp;
                }
                temp = temp->getNext();
            }
        }
        else{
            std::cout << MESSAGE << std::endl;
            return NULL;
        }
}

