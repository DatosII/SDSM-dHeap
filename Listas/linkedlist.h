#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <string.h>
#include <iostream>
#include "Pointer/d_pointer_size_type.h"
#include "Nodos/node_ll.h"

#define JUMP "\n"
#define MESSAGE "DATO NO ENCONTRADO"
#define CERO 0

using namespace std;

struct d_pointer{
    int ip;
    int direccion;
};

/**
 * @file linkedlist.h
 * @brief Crea una lista simple enlazada
 * @author Juan Pablo Brenes Coto
 * @date 15/8/2015
 */
    class  LinkedList {

        public:
            LinkedList();
            ~LinkedList();

            Node_LL* getHead();
            void insert(const string &pData1,const string &pData2);
            void remove(const string& pData1);
            Node_LL* find(char *pIP);
            void print();
            /**
             * @brief operator = Operador de asignacion para borrar
             * datos de la memoria remota.
             * @param pToFree puntero con los datos del objeto a borrar.
             */
//            void operator = (const d_pointer_size_type pToFree);

        private:
            Node_LL *_head;
            Node_LL *_tail;
    };

#endif // LINKEDLIST_H
