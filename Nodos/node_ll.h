#ifndef NODE_LL_H
#define NODE_LL_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <string.h>
#include "Heap/dheap.h"

#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define ERROR "Error al crear el socket cliente"
#define FINCONNEXION "Conexion terminada. La conexion con el SDS  finalizo\n\n"
#define CONECTADO "Estas conectado?"
#define SI "Si"
#define BUFFSIZE 1024

/**
 *Template que usaremos para pasar los parametros que se
 * necesitan para crear la comunicacion cliente con servidor.
 */
struct parametrosInicioCliente{
    std::string IP;
    int PUERTO;
    void* salidaDeInfo;
};


/**
 * @file node_ll.h
 * @brief Crea un nodo para ser utilizado por la lista simple
 * @author Juan Pablo Brenes
 * @date 15/8/2015
 */

    class Node_LL{
    public:
        //Constructor
        Node_LL(const std::string &pData1, const std::string &pData2);

//        Getter y Setter del dato
        char* getIP();

        //Getter y Setter del siguiente nodo
        Node_LL *getNext();
        void setNext(Node_LL *pNext);

        Node_LL* getPrevious();
        void setPrevious(Node_LL* pPrevious);

        unsigned int getInicio();
        unsigned int getFinal();
        unsigned int getTotal();

        int getFlag();
        void setFlag(int pFlag);

        char* getMsg();
        void setMsg(char* pMsg);

        bool getActivo();
        void setActivo(bool pActivo);

        int getPuerto();

		unsigned char *getBytesIp();

        pthread_mutex_t getMutex();

    private:
        unsigned int _inicio; //Variable de inicio de memoria local
        unsigned int _final;  //Variable de final de memoria local
        unsigned int _total;
        unsigned int _PUERTO;//Numero de puerto por el que conversan
		bool _activo = true;
        char* _IP;  // Ip de la maquina a la que se conectara
		unsigned char *_ipBytes;
        int flag;
        char* Msg;
        pthread_t  hiloCliente;
        pthread_mutex_t mutex;
        Node_LL *_next;
        Node_LL *_previous;
        parametrosInicioCliente* parametros;
        static void* conectarClientes(void *pParametros);
        void setDimension(char* pBuffer);
		void setUpBytesIP(); //Método que guarda en un arreglo los bytes de la ip
    };

#endif // NODE_LL_H
