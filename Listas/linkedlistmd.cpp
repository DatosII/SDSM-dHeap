#include "Listas/linkedlistmd.h"

/**
 * @brief LinkedListMD::LinkedListMD Metodo que inicializa el mutex
 * que juzgara las acciones dentro de la lista. Esta ademas controla
 * las entradas del Garbaje Collector a la misma.
 */
LinkedListMD::LinkedListMD(): _head(CERO), _tail(CERO), _totalNodes(CERO)
{
    hiloMutex = PTHREAD_MUTEX_INITIALIZER;
}


/**
* @brief Método que permite insertar un nuevo dato en la lista
*
* @param pData Dato que se quiere insertar dentro de la lista
*/
void LinkedListMD::insert(d_pointer_size_type *pPointer) {

    pthread_mutex_lock(&hiloMutex);

    Node_MD *newNode = new Node_MD(pPointer);

    if (_head == CERO){
        _head = _tail = newNode;
		_totalNodes++;
    }
    else{
        Node_MD *tmp = _head;
        while((*tmp).getNext() != CERO){
            tmp = tmp->getNext();
        }
        tmp->setNext(newNode);
        _tail = tmp;
		_totalNodes++;
    }
    pthread_mutex_unlock(&hiloMutex);
}


/**
 * @brief LinkedListMD::remove
 * Recorre la lista comparando el dato almacenado por cada nodo
 * con el dato que se quiere eliminar, cuando se encuentra el
 * nodo que almacena el dato, este es eliminado
 * @param pPointer es el puntero por el cual buscaremos el nodo a borrar.
 */
void LinkedListMD::remove(d_pointer_size_type pPointer){
    if(_head == CERO){ //Lista esta vacia
        return;
    }
    else if(*(_head->getData()) == pPointer){ //Dato se encuentra en el head
        Node_MD *temp = _head;
        _head = _head->getNext();
		_totalNodes--;
        delete temp;
    }
    else{ //Dato no esta en el head, se debe buscar
        Node_MD *prev = _head, *next = _head->getNext();
        while(next != CERO){
            if(*(next->getData()) == pPointer){
                prev->setNext(next->getNext());

                if(next == _tail){
                    _tail = prev;
                }
				_totalNodes--;
                delete next;
                break;
            }

            prev = next;
            next = next->getNext();
        }
    }
}


/**
 * @brief LinkedListMD::find
 * Recorre la lista comparando el dato almacenado en cada nodo
 * con el dato que se busca, si se encuentra el nodo que contiene
 * el dato, este se retorna; en caso constrario se retorna NULL
 * @param pPointer Es el puntero con el cual vamos a realizar la lista.
 * @return El puntero del nodo buscado.
 */
Node_MD *LinkedListMD::find(d_pointer_size_type pPointer){
    pthread_mutex_lock(&hiloMutex);
    if(_head != CERO){
        Node_MD *temp = _head;
        while(temp != CERO){
            if(*(temp->getData()) == pPointer){
                  pthread_mutex_unlock(&hiloMutex);
                return temp;
            }
            temp = temp->getNext();
        }
    }
    else{
        std::cout << MESSAGE << JUMP;
          pthread_mutex_unlock(&hiloMutex);
        return NULL;
    }

}


/**
 * @brief Método que busca un d_pointer_size_type segun su ID
 *
 * @param pID ID del d_pointer_size_type
 *
 * @return d_pointer_size_type con el id buscado
 */
d_pointer_size_type *LinkedListMD::findByID(unsigned int pID){
	pthread_mutex_lock(&hiloMutex);
	if(_head != CERO){
		Node_MD *temp = _head;
        while(temp != CERO){
            if(temp->getData()->getID() == pID){
                pthread_mutex_unlock(&hiloMutex);
                return temp->getData();
			}
			temp = temp->getNext();
        }
	}
	else{
		std::cout << MESSAGE << JUMP;
        pthread_mutex_unlock(&hiloMutex);
		return NULL;
	}

}


/**
* @brief Método que imprime todos los datos almacenados dentro de la lista
*/
void LinkedListMD::print(){
    pthread_mutex_lock(&hiloMutex);
    Node_MD *tmp = _head;
    while(tmp != CERO){
        std::cout << tmp->getData() << JUMP;
        tmp = tmp->getNext();
    }
    pthread_mutex_unlock(&hiloMutex);
}


/**
* @brief Método que retorna el puntero head de la lista
*
* @return Head de la lista
*/
Node_MD *LinkedListMD::getHead() {
    return this->_head;
}


/**
 * @brief Método que permite obtiener la cantida de nodos dentro de la lista
 * @return Cantidad de nodos
 */
unsigned int LinkedListMD::getTotalNodes(){
	return _totalNodes;
}


/**
* @brief Destructor de la clase
*
* Recorre toda la lista borrando los punteros a cada nodo
*/
LinkedListMD::~LinkedListMD(){
    if(_head != CERO){
        Node_MD *current = _head;
        Node_MD *next;

        while(current->getNext() != 0){
            next = current->getNext();
            delete current;
            current = next;
        }
    }
}


/**
 * @brief LinkedListMD::iniciarGarbaje Metodo que inicializa el thread del GarbajeCollector
 * @param pFrecuency es la frecuencia de revision sobre la lista que tendra el Garbaje.
 */
void LinkedListMD::iniciarGarbaje(string pFrecuency){

    parametros = new parametrosGarbaje();

    parametros->frecuencia = atoi(pFrecuency.c_str());
    parametros->listaMetadatos = this;
    parametros->mutexStruct = hiloMutex;

    std::cout<<"Me encuentro en iniciar Garbaje"<<std::endl;
    pthread_create(&hiloGarbaje,NULL,garbajeCollector,parametros);
}


/**
 * @brief LinkedListMD::garbajeCollector hilo que
 * revisa las referencias de los metadatos para
 * conocer si se tienen que eliminar automaticamente o no.
 * @param pParametros struct con el mutex y la frecuencia necesarios para el garbaje.
 */
void* LinkedListMD::garbajeCollector(void *pParametros){
    std::cout<<"Me encuentro en el Garbaje Collector"<<std::endl;
    int _inicio = CERO;
    int _final = CERO;
    _inicio = _final = time(NULL);
    while(true){
        while(_final-_inicio < ((parametrosGarbaje*)pParametros)->frecuencia)
            _final = time(NULL);
        //std::cout<<"Estoy dentro del ciclo de frecuencia del garbaje collector"<<std::endl;
         Node_MD* _temp= ((LinkedListMD*)((parametrosGarbaje*)pParametros)->listaMetadatos)->getHead();

		while(_temp != NULL){
			pthread_mutex_lock(&(((parametrosGarbaje*)pParametros)->mutexStruct));

            if (_temp->CantidadReferencias() == 0){
                Node_MD* _temp2 = _temp->getNext();
//                dHeap::instancia()->dFree(*(_temp->getData()));  //////////////////Falta desarrollar esta seccion.
                ((LinkedListMD*)((parametrosGarbaje*)pParametros)->listaMetadatos)->remove(*(_temp->getData()));
                _temp = _temp2;
            }
            else
                _temp = _temp->getNext();

			pthread_mutex_unlock(&(((parametrosGarbaje*)pParametros)->mutexStruct));

            _inicio = _final = time(NULL);
        }
        _inicio = _final = time(NULL);
    }
}
