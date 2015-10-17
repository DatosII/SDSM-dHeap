#include "nodoapp.h"
/**
 * @brief NodoApp::NodoApp, constructor de la clase
 * @param pDObject
 */
NodoApp::NodoApp(dObject *pDObject){
    this->_data=pDObject;
    this->_next = NULL;
    this->_id=pDObject->getID();
}
/**
 * @brief NodoApp::setNext, Modifica el siguiente nodo
 * @param pNext
 */
void NodoApp::setNext(NodoApp *pNext){
    this->_next=pNext;
}
/**
 * @brief NodoApp::getNext, Obtiene el siguiente nodo
 * @return siguiente nodo
 */
NodoApp* NodoApp::getNext(){
    return this->_next;
}
/**
 * @brief NodoApp::getId, Obtiene el id
 * @return id
 */
unsigned int NodoApp::getId(){
    return _id;
}
/**
 * @brief NodoApp::getData, obtiene el dObject (data)
 * @return dato
 */
dObject *NodoApp::getData(){
    return _data;
}

