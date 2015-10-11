#include "Listas/linkedlist.h"

/**
* @brief Constructor por defecto de la clase.
*/

LinkedList::LinkedList(): _head(CERO), _tail(CERO)
{
}

/**
 * @brief LinkedList::insert Metodo que inserta un nuevo dato en la lista
 * @param pData1 Es un string que representa el ip de la maquina.
 * @param pData2 Es un string que representa el puerto de la maquina.
 */
void LinkedList::insert(const string &pData1,const string &pData2) {

	Node_LL *newNode = new Node_LL(pData1, pData2);
    if (_head == CERO){
        _head = _tail = newNode;
    }
    else{
        Node_LL *tmp = _head;
        while((*tmp).getNext() != CERO){
            tmp = tmp->getNext();
        }
        tmp->setNext(newNode);
        tmp->getNext()->setPrevious(tmp);
        _tail = tmp;
    }
}

/**
 * @brief LinkedList::remove
 * Recorre la lista comparando el dato almacenado por cada nodo
 * con el dato que se quiere eliminar, cuando se encuentra el
 * nodo que almacena el dato, este es eliminado
 * @param pData1 Es un string que representa el Ip de la maquina almacenado en el nodo.
 */
void LinkedList::remove(const string &pData1){
    if(_head == CERO){ //Lista esta vacia
        return;
    }
    else if(_head->getIP() == pData1){ //Dato se encuentra en el head
        Node_LL *temp = _head;
        _head = _head->getNext();
        _head->setPrevious(NULL);
        delete temp;
    }
    else{ //Dato no esta en el head, se debe buscar
        Node_LL *prev = _head, *next = _head->getNext();
        while(next != CERO){
            if(next->getIP() == pData1){
                prev->setNext(next->getNext());

                if(next == _tail){
                    _tail = prev;
                    _tail->setNext(NULL);
                }
                delete next;
                break;
            }

            prev = next;
            next = next->getNext();
        }
    }
}


/**
* @brief Método que busca un dato dentro de la lista
*
* Recorre la lista comparando el dato almacenado en cada nodo
* con el dato que se busca, si se encuentra el nodo que contiene
* el dato, este se retorna; en caso constrario se retorna NULL
*
* @param pData Dato que se quiere buscar dentro de la lista
*
* @return Nodo que contiene el dato buscado
*/
Node_LL *LinkedList::find(char* pIP){
    if(_head != CERO){
        Node_LL *temp = _head;
        while(temp != CERO){
            if(temp->getIP() == pIP){
                return temp;
            }
            temp = temp->getNext();
        }
    }
    else{
        std::cout << MESSAGE << JUMP;
        return NULL;
    }
}



/**
* @brief Método que retorna el head de la lista
*
* @return Head de la lista
*/
Node_LL* LinkedList::getHead() {
    return this->_head;
}


/**
* @brief Método que imprime todos los datos almacenados dentro de la lista
*/
void LinkedList::print(){
    Node_LL *tmp = _head;
    while(tmp != CERO){
        std::cout << tmp->getIP() << JUMP;
        tmp = tmp->getNext();
    }
}

/**
* @brief Destructor de la clase
*
* Recorre toda la lista borrando los punteros a cada nodo
*/
LinkedList::~LinkedList(){
    if(_head != CERO){
        Node_LL *current = _head;
        Node_LL *next;

        while(current->getNext() != CERO){
            next = current->getNext();
            delete current;
            current = next;
        }
    }
}
