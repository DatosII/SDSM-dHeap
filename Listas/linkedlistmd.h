#ifndef LINKEDLISTMD_H
#define LINKEDLISTMD_H

#include <string>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include "Heap/dheap.h"
#include "Pointer/d_pointer_size_type.h"
#include "Nodos/node_md.h"
#include <stdlib.h>
#include <unistd.h>

#define JUMP "\n"
#define MESSAGE "DATO NO ENCONTRADO"
#define CERO 0

using namespace std;

/**
 * @brief The parametrosGarbaje struct es
 * un struct con la propia lista y con la
 * frecuencia de revision.
 */
struct parametrosGarbaje{
    int frecuencia;
    void* listaMetadatos;
    void* pPunteroDHeap;
    pthread_mutex_t mutexStruct;
};

/**
 * @file linkedlist.h
 * @brief Crea una lista simple enlazada
 * @author Juan Pablo Brenes Coto
 * @date 15/8/2015
 */
class  LinkedListMD {

public:
    LinkedListMD();
    void iniciarGarbaje(string pFrecuency);
    ~LinkedListMD();

    Node_MD *getHead();
    void insert(d_pointer_size_type *pPointer);
    void remove(d_pointer_size_type pPointer);
    Node_MD* find(d_pointer_size_type pPointer);
	d_pointer_size_type* findByID(unsigned int pID); //Método que busca un d_pointer por su id
    void print();

private:
    Node_MD *_head;
    Node_MD *_tail;
    parametrosGarbaje* parametros;
    pthread_t hiloGarbaje;
    pthread_mutex_t hiloMutex;
    static void* garbajeCollector(void* pParametros);
};


#endif // LINKEDLISTMD_H
