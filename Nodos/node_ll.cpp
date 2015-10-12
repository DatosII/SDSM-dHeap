#include "Nodos/node_ll.h"

/**
 * @brief Node_LL::Node_LL Constructor que setea los valores de la clase
 * e inicializa el thread con la estructura del cliente/servidor.
 * @param pData1 Es un string con el IP de la maquina.
 * @param pData2 Es un string con el numero de puerto de la maquina.
 */
Node_LL::Node_LL(const std::string &pData1, const std::string &pData2){

    this->_IP = (char*)pData1.c_str();
	this->setUpBytesIP();
    this->_PUERTO = atoi(pData2.c_str());
    this->_next = CERO;

    mutex = PTHREAD_MUTEX_INITIALIZER;

    parametros =  new parametrosInicioCliente();
    parametros->IP = pData1;
    parametros->PUERTO = this->_PUERTO;
    parametros->salidaDeInfo = this;

    this->flag=CERO;

    //Creamos el hilo que ejecutara la coneccion con el SDS que se especifico con
    //el ip y puerto que se pasaron como parametros.
    pthread_create(&hiloCliente,NULL,conectarClientes,parametros);
}


/**
 * @brief Método que retorna el dato almacenado por el nodo (IP de la maquina).
 *
 * @return Dato almacenado por el nodo
 */

char* Node_LL::getIP() {
    return this->_IP;
}


/**
 * @brief Método que permite obtener el siguiente nodo
 *
 * @return Nodo siguiente
 */
Node_LL *Node_LL::getNext() {
    return this->_next;
}



/**
 * @brief Método que permite establecer el siguiente nodo
 *
 * @param pNext Nodo siguiente
 */
void Node_LL::setNext(Node_LL *pNext) {
    this->_next = pNext;
}

/**
 * @brief Node_LL::getPrevious Metodo que retorna el Nodo
 * previo al actual
 * @return un puntero a un objeto Node_LL
 */
Node_LL* Node_LL::getPrevious(){
    return this->_previous;
}

/**
 * @brief Node_LL::setPrevious Establece el nodo previo al actual.
 * @param pPrevious Es el nodo que deseamos establecer.
 */
void Node_LL::setPrevious(Node_LL* pPrevious){
    this->_previous = pPrevious;
}

/**
 * @brief Node_LL::getInicio Metodo que retorna el inicio
 * de memoria del nodo (abstraccion de la direccion).
 * @return un entero que indica el comienzo de la memoria.
 */
unsigned int Node_LL::getInicio(){
    return this->_inicio;
}

/**
 * @brief Node_LL::getFinal Metodo que retorna el final
 * de la memoria del nodo
 * @return un entero que inidica el final de la memoria.
 */
unsigned int Node_LL::getFinal(){
    return this->_final;
}

/**
 * @brief Node_LL::getTotal Metodo que retorna el total de memoria del nodo.
 * @return un entero con la cantidad de memoria del nodo.
 */
unsigned int Node_LL::getTotal(){
    return this->_total;
}

/**
 * @brief Node_LL::getActivo Metodo que retorna un booleano indicando
 * si el nodo esta conectado a un SDS o no.
 * @return un booleano que indica la conexion con el SDS.
 */
bool Node_LL::getActivo(){
    return this->_activo;
}

/**
 * @brief setActivo Metodo que setea el valor de activo
 * del Nodo(conectado o no).
 * @param pActivo es el nuevo valor de activacion del nodo.
 */
void Node_LL::setActivo(bool pActivo){
    this->_activo = pActivo;
}

/**
 * @brief Node_LL::getPuerto Metodo que retorna el numero de puerto.
 * @return un entero que representa el numero de puerto.
 */
int Node_LL::getPuerto(){
    return this->_PUERTO;
}


/**
 * @brief Node_LL::setDimension Metodo que establece los parametos
 * de inicio, final y total de la memoria del nodo.
 * @param pBuffer es el mensaje recibido por el servidor para establecer
 * los parametros mencionados.
 */
void Node_LL::setDimension(char* pBuffer){
    if(this->_previous == NULL){
        this->_inicio = 0;
        this->_final = (*(unsigned int*)pBuffer)-1;
        this->_total = (*(unsigned int*)pBuffer);
    }
    else{
        this->_total = *(unsigned int*)pBuffer;
        this->_inicio = this->getPrevious()->getFinal()+1;
        this->_final = this->_inicio + this->_total-1;
    }
}



/**
 * @brief Node_LL::conectarClientes Metodo que inicia el protocolo
 * Cliente/Servidor y transmite mensajes por medio de banderas y mutex
 * @param pParametros Es un struct con los parametros necesarios para
 * la comunicacion entre maquinas
 * @return
 */
void* Node_LL::conectarClientes(void* pParametros){

    dHeap* heap = dHeap::instancia();
    pthread_mutex_t mutexTemporal = ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->getMutex();

    int cliente;
    int puerto=((parametrosInicioCliente*)pParametros)->PUERTO;
    char* buffer=new char[BUFFSIZE];
	std::string ip = ((parametrosInicioCliente*)pParametros)->IP;
	char* ipTemp = (char*)ip.c_str();

	for(int i=0; i<ip.length();i++){
		if(ipTemp[i] == 0) ipTemp[i] = 0x2e;
	}

    struct sockaddr_in direc;
    if ((cliente=socket(AF_INET,SOCK_STREAM,0))<0){
        std::cout<<ERROR<<std::endl;
        exit(CERO);
    }

    direc.sin_family=AF_INET;
	direc.sin_port=htons(puerto);
	inet_pton(AF_INET,ipTemp,&direc.sin_addr);

    if (connect(cliente,(struct sockaddr *)&direc,sizeof(direc))==CERO){
        //En caso de conectarse se establece el protocolo preestablecido
        ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setActivo(true);

        recv(cliente,buffer,BUFFSIZE,CERO);
        ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setDimension(buffer);

        while(true){
            //Por medio de la bandera evalua el buffer hasta encontrar el siguiente recv()
			//recv(cliente,buffer,BUFFSIZE,MSG_PEEK);

            //Accesamos a la memoria compartida por el dHeap y el Nodo_LL
            pthread_mutex_lock(&mutexTemporal);

            if(((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->getFlag()==UNO){

                ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setFlag(DOS);

                send(cliente,((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->getMsg()
                     ,BUFFSIZE,CERO);
                recv(cliente,buffer,BUFFSIZE,CERO);
//                if(strcmp(buffer, CONECTADO) == CERO ){

//                    send(cliente,SI,BUFFSIZE,CERO);
//                    send(cliente,((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->getMsg()
//                         ,BUFFSIZE,CERO);
//                    recv(cliente,buffer,BUFFSIZE,CERO);
//                    ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setMsg(buffer);
//                    ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setFlag(TRES);

//                }

//                else{

                    ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setMsg(buffer);
                    ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setFlag(TRES);
//                }
            }

            pthread_mutex_unlock(&mutexTemporal);
        }

        std::cout<<FINCONNEXION;
        close(cliente);

    }

    else{
        std::cout<<"Error.No se pudo conectar al servidor." <<std::endl;
        ((Node_LL*)((parametrosInicioCliente*)pParametros)->salidaDeInfo)->setActivo(false);
    }
    return CERO;
}

/**
 * @brief Node_LL::getFlag Metodo que retorna el valor de la
 * bandera de mensajes.
 * @return un entero que representa la bandera de ejecucion.
 */
int Node_LL::getFlag(){
    return this->flag;
}

/**
 * @brief Node_LL::setFlag Metodo que setea el valor de la
 * bandera de mensajeria.
 * @param pFlag es el nuevo valor para la bandera.
 */
void Node_LL::setFlag(int pFlag){
    this->flag=pFlag;
}

/**
 * @brief Node_LL::setMsg Metodo para setear el mensaje para el
 * servidor o para el dHeap.
 * @param pMsg es el nuevo valor de mensaje.
 */
void Node_LL::setMsg(char *pMsg){
    this->Msg=pMsg;
}

/**
 * @brief Node_LL::getMsg Metodo que retorna el mensaje.
 * @return un char* con el mensaje.
 */
char* Node_LL::getMsg(){
    return this->Msg;
}

/**
 * @brief Node_LL::getMutex Metodo que retorna el mutex del nodo.
 * @return un mutex que sincronizara la comunicacion entre los
 * mensajes del dHeap y los mensajes del Servidor.
 */
pthread_mutex_t Node_LL::getMutex(){
    return mutex;
}


/**
 * @brief Método que guarda en un arreglo los bytes que representan la ip
 * del SDSMNode
 */
void Node_LL::setUpBytesIP(){
	this->_ipBytes = new unsigned char[4];
	std::stringstream ss;
	char *pch;
	pch = strtok(this->_IP, ".");
	int i = 0;
	while(pch !=NULL){
		std::string tmp = (std::string)pch;
		ss << std::setfill('0') << std::setw(2) <<  std::hex << std::stoi(tmp);
		_ipBytes[i] = strtol(ss.str().c_str(), NULL, 16);
		pch = strtok(NULL, ".");
		i++;
		ss.str("");
	}
}



/**
 * @brief Método para obtener los bytes que representan la ip de SDSMNode
 *
 * @return Bytes de la ip
 */
unsigned char *Node_LL::getBytesIp(){
	return this->_ipBytes;
}

