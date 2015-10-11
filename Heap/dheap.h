#ifndef DHEAP_H
#define DHEAP_H

#include <string>
#include <string.h>
#include "Pointer/d_pointer_size_type.h"


#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <pthread.h>
#include <sstream>
#include <iomanip>

#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define OCHO 8

#define DSET "d_set:"
#define DCALLOC "d_calloc:"

using namespace std;

/**
 * @brief The dHeap class Clase que abstrae el concepto de memoria
 * compartiendola en sus diferentes servidores. Solo posee los
 * datos relativos a la localizacion de la informacion.
 */
class dHeap{

public:
    static dHeap* instancia(void* pListServer, void* pListMetadata);
    static dHeap* instancia();
    d_pointer_size_type* dMalloc(unsigned int size, char type);
    unsigned char* dSet(d_pointer_size_type* pPointer, unsigned char* pBytes, unsigned char* pByStream);
    void dFree(d_pointer_size_type toFree);
	unsigned char* makedStatus();
	unsigned char* intToBytes(unsigned int pInt);
	unsigned char* floatToBytes(float pFloat);
	unsigned char* stringToBytes(std::string pString);
    void* getListaDeServidores();
    void* getListaMD();
    ~dHeap();

private:
    static dHeap* miInstancia;
    void* metadatos;
    void* listaDeServidores;

    /** Declaracion de los metodos privados de nuestro dHeap*/
    dHeap(void *pListServer, void *pListMetadata);

    unsigned char* makedCalloc(unsigned char* one, unsigned char* two);
    unsigned char* makedSet(unsigned char word[], unsigned char* ip, unsigned char* port, unsigned char* bytes, unsigned char* bystream);
    unsigned char* makedGet(unsigned char word[], unsigned char* ip, unsigned char* port, unsigned char* pMem, unsigned char* pBytes);
    unsigned char* makedFree(unsigned char word[], unsigned char* ip, unsigned char* port, unsigned char* pMem, unsigned char* pBytes);
    unsigned int request(unsigned int pSize, d_pointer_size_type *pPointer);
    unsigned char* makeIp(std::string pIp);
    unsigned char* shortToBytes(unsigned short pShort);

    /** Realizamos la sobrecarga del operador de igualdad*/
    dHeap* operator=(const dHeap heap);
};

#endif // DHEAP_H
