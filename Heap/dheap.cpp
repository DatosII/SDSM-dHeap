#include "Heap/dheap.h"
#include "Listas/linkedlist.h"
#include "Listas/linkedlistmd.h"


/**
 * @brief dHeap::miInstancia instancia unica del dHeap. Se declara
 * en el archivo .cpp por ser una clase singleton.
 */
dHeap* dHeap::miInstancia = CERO;



/**
 * @brief dHeap::operator = Sobrecarga del operador de
 * igualdad que evita alguna copia del dHeap.
 * @param heap es el objeto dHeap que se desea sobreescribir.
 * @return un objeto del tipo dHeap.
 */
dHeap* dHeap::operator =(const dHeap heap){
    return miInstancia;
}



/**
 * @brief dHeap::dHeap Constructor privado del dHeap que
 * inicializa las listas que trabajan en el.
 * @param pListServer Es la lista con la conexion de los servidores.
 * @param pListMetadata Es la lista con los metadatos de la informacion almacenada.
 */
dHeap::dHeap(void* pListServer, void* pListMetadata)
{
    metadatos = pListMetadata;
    listaDeServidores = pListServer;
}



/**
 * @brief dHeap::instancia Metodo que limita el numero
 * de instancias de esta clase a solo una.
 * @param path es la ruta del archivo de configuracion.
 * @return un objeto dHeap.
 */
dHeap* dHeap::instancia(void *pListServer, void *pListMetadata)
{
    if (miInstancia == CERO)
        miInstancia = new dHeap(pListServer, pListMetadata);
    return miInstancia;
}



/**
 * @brief dHeap::instancia metodo sobrecargado que
 * retorna la instancia unica del dHeap
 * @return un puntero del dHeap
 */
dHeap* dHeap::instancia()
{
    return miInstancia;
}



/**
 * @brief dHeap::getListaDeServidores Getter que retorna la lista
 * con las conexiones a los SDS.
 * @return un puntero void de la lista.
 */
void* dHeap::getListaDeServidores(){
    return listaDeServidores;
}



void* dHeap::getListaMD(){
    return metadatos;
}



/**
 * @brief Método que reserva espacio en algun SDSMNode conectado
 *
 * Crea un nuevo d_pointer_size_type con el tipo enviando como parametro,
 * luego se llama al método request el cual busca algun SDSMNode con espacio,
 * en donde envia el mensaje con la cantidad de bytes a reservar. Se asigna
 * al d_pointer creado la dirección de memoria virtual donde se encuentra
 * el espacio en el dHeap
 *
 * @param size Tamaño a reservar
 *
 * @param type Tipo de dato
 *
 * @return d_pointer_size_type al espacio reservado
 */
d_pointer_size_type* dHeap::dMalloc(unsigned int size, char type){
		d_pointer_size_type*  pointer = new d_pointer_size_type();
        pointer->setType(type);
        unsigned int address = request(size,pointer);
        if(address != -1){
			pointer->setPtr(address);
            //std::cout << "ADDRESS: " << address << "\n";
			pointer->setSpace(size);
            pointer->setRef(1);
			dHeap *heap = dHeap::instancia();
			((LinkedListMD*)heap->getListaMD())->insert(pointer);
		}
        return pointer;
}



/**
 * @brief Método que permite almacenar bytes dentro de algun espacio reservado
 *
 * Utiliza los parametro del d_pointer para encontrar el SDSMNode donde se reservo
 * memoria, luego envia el mensaje con los parametros necesarios para que el
 * SDSMMemoryNode almacene los bytes dentro del espacio reservado
 *
 * @param pPointer d_pointer al espacio reservado
 * @param pBytes Cantidad de bytes a enviar
 * @param pByStream Bytes a enviar
 *
 * @return
 */
unsigned char* dHeap::dSet(d_pointer_size_type* pPointer, unsigned char* pBytes, unsigned char* pByStream){

    std::cout<<"Estoy al comienzo del dSet()"<<std::endl;

    unsigned char* _ip = pPointer->getIp();
    unsigned char* _puerto = this->shortToBytes((unsigned short)pPointer->getPuerto());

    unsigned char _arreglo[] = DSET;
    unsigned char* ptr = _arreglo;
	unsigned char* _message = this->makedSet(ptr, pPointer->getIpBytes(),_puerto,intToBytes(pPointer->getPtr()),pBytes,pByStream);

	bool flag = true;
	unsigned char *pData;

	Node_LL* nodoDeEnvio = ((LinkedList*)this->getListaDeServidores())->find((char*)_ip);
    pthread_mutex_t mutexTemporal = nodoDeEnvio->getMutex();
    pthread_mutex_lock(&mutexTemporal);

     nodoDeEnvio->setMsg((char*)_message);
    nodoDeEnvio->setFlag(UNO);
    pthread_mutex_unlock(&mutexTemporal);
	while(flag){
        pthread_mutex_lock(&mutexTemporal);
        if(nodoDeEnvio->getFlag()==TRES){
            flag = false;
        }
        pthread_mutex_unlock(&mutexTemporal);
    }
    pthread_mutex_lock(&mutexTemporal);
    pData= (unsigned char*)nodoDeEnvio->getMsg();
    nodoDeEnvio->setFlag(CERO);

    pthread_mutex_unlock(&mutexTemporal);
    std::cout << "RETURN SET: "; std::printf("%x\n", pData[0]);
	if(pData[0] == CERO){
        return _ip;
    }
    else{
        return CERO;
    }
}



unsigned char *dHeap::dGet(d_pointer_size_type *pPointer, unsigned char *pBytes, unsigned char *pBytesAddress){
    std::cout<<"Estoy al comienzo del dGet()"<<std::endl;

    unsigned char* _ip = pPointer->getIp();
    unsigned char* _puerto = this->shortToBytes((unsigned short)pPointer->getPuerto());

    unsigned char _arreglo[] = DGET;
    unsigned char* ptr = _arreglo;
    unsigned char* _message = this->makedGet(ptr, pPointer->getIpBytes(), _puerto, pBytesAddress, pBytes);

    bool flag = true;
    unsigned char *pData;

    Node_LL* nodoDeEnvio = ((LinkedList*)this->getListaDeServidores())->find((char*)_ip);
    pthread_mutex_t mutexTemporal = nodoDeEnvio->getMutex();
    pthread_mutex_lock(&mutexTemporal);

     nodoDeEnvio->setMsg((char*)_message);
    nodoDeEnvio->setFlag(UNO);
    pthread_mutex_unlock(&mutexTemporal);
    while(flag){
        pthread_mutex_lock(&mutexTemporal);
        if(nodoDeEnvio->getFlag()==TRES){
            flag = false;
        }
        pthread_mutex_unlock(&mutexTemporal);
    }
    pthread_mutex_lock(&mutexTemporal);
    pData= (unsigned char*)nodoDeEnvio->getMsg();
    nodoDeEnvio->setFlag(CERO);
    pthread_mutex_unlock(&mutexTemporal);
    std::cout << "RETURN GET: "; std::printf("%x\n", pData[0]);
    if(pData[0] == CERO){
        return pData+1;
    }
    else{
        return CERO;
    }
}



/**
 * @brief dHeap::dFree
 * @param toFree
 */
void dHeap::dFree(d_pointer_size_type* toFree){
    std::cout<<"Estoy al comienzo del dFree()"<<std::endl;

    unsigned char* _ip = toFree->getIp();
    unsigned char* _puerto = this->shortToBytes((unsigned short)toFree->getPuerto());

    unsigned char _arreglo[] = DFREE;
    unsigned char* ptr = _arreglo;

    unsigned int _realAddress = addressInSDS(toFree->getPtr());
    unsigned char *bytesAddress = intToBytes(_realAddress);
    unsigned char *bytesToFree = intToBytes(toFree->getSpace());

    unsigned char* _message = this->makedFree(ptr, toFree->getIpBytes(), _puerto, bytesAddress, bytesToFree);

    delete bytesAddress, bytesToFree;

    bool flag = true;
    unsigned char *pData;

    Node_LL* nodoDeEnvio = ((LinkedList*)this->getListaDeServidores())->find((char*)_ip);
    pthread_mutex_t mutexTemporal = nodoDeEnvio->getMutex();
    pthread_mutex_lock(&mutexTemporal);

     nodoDeEnvio->setMsg((char*)_message);
    nodoDeEnvio->setFlag(UNO);
    pthread_mutex_unlock(&mutexTemporal);
    while(flag){
        pthread_mutex_lock(&mutexTemporal);
        if(nodoDeEnvio->getFlag()==TRES){
            flag = false;
        }

        pthread_mutex_unlock(&mutexTemporal);
    }
    pthread_mutex_lock(&mutexTemporal);
    pData= (unsigned char*)nodoDeEnvio->getMsg();
    nodoDeEnvio->setFlag(CERO);

    pthread_mutex_unlock(&mutexTemporal);
    std::cout << "RETURN FREE: "; std::printf("%x\n", pData[0]);
    if(pData == CERO){
        toFree->setRef(-1);
    }

}



/**
 * @brief Método reserva espacio en los SDSMMemoryNode mediante el dCalloc
 *
 * Crea el mensaje que se debe enviar, y recorre la lista de SDSMNode hasta encontrar
 * uno con espacio suficiente para reservar el espacio deseado.
 * La lista se recorre llevando un offset, el cual es la memoria total del SDSMNode
 * anterior al que se envio el mensaje; de modo que cuando retorna la direccion
 * virtual en memoria, se suma este offset
 *
 * @param size Cantidad de espacio a reservar
 * @param pPointer d_pointer con los parametro necesarios para conectar con el SDS
 *
 * @return Direccion de memoria virtual
 */
unsigned int dHeap::request(unsigned int size, d_pointer_size_type* pPointer){

    bool loopDel3 = true;

	unsigned char word[] = DCALLOC ;
    unsigned char*  ptrw= word;
    unsigned char *byte = intToBytes(size);
	unsigned char* pData= makedCalloc(ptrw, byte);
	unsigned char *Returned;

    Node_LL *tmp=((LinkedList*)listaDeServidores)->getHead();
    pthread_mutex_t mutexTemporal = tmp->getMutex();
    unsigned int offset = CERO;

    while(tmp != NULL){
		if(tmp->getActivo()!=false){
			pthread_mutex_lock(&mutexTemporal);
			tmp->setMsg((char*)pData);
			tmp->setFlag(UNO);
			pthread_mutex_unlock(&mutexTemporal);
			while(loopDel3){
				pthread_mutex_lock(&mutexTemporal);
				if(tmp->getFlag()==TRES)
					loopDel3 = false;
				pthread_mutex_unlock(&mutexTemporal);
			}
			pthread_mutex_lock(&mutexTemporal);
			Returned= (unsigned char*)tmp->getMsg();
			tmp->setFlag(CERO);
			pthread_mutex_unlock(&mutexTemporal);
			if(Returned[CERO]==UNO){
				offset += tmp->getTotal();
				tmp=tmp->getNext();
				mutexTemporal =tmp->getMutex();
			}
			else
				break;
		}
		else
			break;
	}
    if(tmp==NULL || tmp->getActivo()==false)
        return -1;
    else {
		std::cout << "VALOR RETORNADO" << "\n";				/////////////////////////////////////////////////
		for(int i=0; i<11; i++) std::printf("%x\n", Returned[i]);
		pPointer->setIp((unsigned char*)tmp->getIP());
		pPointer->setIpBytes(tmp->getBytesIp());
        pPointer->setPuerto((short)tmp->getPuerto());
		unsigned char* tmpAdd= Returned+7;
        unsigned int address = *((unsigned int*)tmpAdd);
        return address+offset;
    }
}



/**
 * @brief Método que obtiene la representación en bytes de un int
 *
 * @param pInt Número al que quieren obtenerse los bytes
 *
 * @return Puntero a un arreglo con los bytes del numero
 */
unsigned char* dHeap::intToBytes(unsigned int pInt){
    unsigned char* bytes= new unsigned char[CUATRO];
    for (int index = CERO, byte=CERO; index<CUATRO, byte<=TRES; index++, byte++)
        bytes[index]=pInt>>(OCHO*byte)&0xFF;
    return bytes;
}



/**
 * @brief Método que obtiene obtiene la representacion en bytes de un dato
 * tipo float
 *
 * @param pFloat Float al que se quiere obtener su representacion en bytes
 *
 * @return Arreglo de bytes
 */
unsigned char *dHeap::floatToBytes(float pFloat){
	unsigned char *ptrTemp = (unsigned char*)&pFloat;
	unsigned char *arr = new unsigned char[4];

	for(int i = 0; i < 4; i++){
		arr[i] = *(ptrTemp+i);
	}

	return arr;
}



/**
 * @brief Método que obtiene la representacion en bytes de un short
 *
 * @param pShort Numero al que se quiere obtener su representacion en bytes
 *
 * @return Arreglo de bytes
 */
unsigned char* dHeap::shortToBytes(unsigned short pShort){
	unsigned char* bytes = new unsigned char[DOS];

	bytes[CERO] = (pShort & 0xFF00) >> OCHO;
    bytes[UNO] = pShort & 0x00FF;

	return bytes;
}



/**
 * @brief Método para obtener la representacion en bytes de un string
 *
 * @param pString String al que se quiere obtener su representacion en bytes
 *
 * @return Arreglo de bytes
 */
unsigned char* dHeap::stringToBytes(string pString){
	unsigned char *ptrTemp = (unsigned char*)pString.c_str();
	unsigned char *arr = new unsigned char[pString.length()];

	for(int i = 0; i < pString.length(); i++){
		arr[i] = *(ptrTemp+i);
	}

	return arr;
}



/**
 * @brief Método que forma el mensaje para ejecutar un d_calloc
 *
 * @param pOne Cadena "d_calloc:"
 * @param pTwo Arreglo bytes con la cantidad de bytes a reservar
 *
 * @return Puntero que une los parametros
 */
unsigned char* dHeap::makedCalloc(unsigned char* pWord, unsigned char* pSize){
	unsigned char *pData;

	std::stringstream ss;
	ss << pWord;
	for(int i = 0; i < 4; i++)
		ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(pSize[i]);
	std::string temp = ss.str();
    std::cout << "MENSAJE DCALLOC: " << temp << std::endl;
	pData = (unsigned char*)ss.str().c_str();

	return pData;
}



/**
 * @brief Método que forma el mensaje para ejecutar un d_set
 *
 * @param word Cadena "d_set:"
 * @param ip Arreglo con los bytes de la ip
 * @param port Arreglo con los bytes del puerto
 * @param bytes Arreglo con la cantidad de bytes a almacenar
 * @param bystream Arreglo con los bytes a almacenar
 *
 * @return Puntero con la union de todos los parametros
 */
unsigned char* dHeap::makedSet(unsigned char *word, unsigned char* ip,
							   unsigned char* port, unsigned char* address, unsigned char* bytes, unsigned char* bystream){

    unsigned char* pData;
    std::stringstream ss;
		ss << word;
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(ip[i]);
    for(int i=CERO; i<DOS;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(port[i]);
	for(int i=CERO; i<CUATRO;i++)
		ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(address[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(bytes[i]);
    unsigned int* numBytes = (unsigned int*)bytes;
    for(int i=CERO; i<*numBytes;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(bystream[i]);
    std::string tmp=ss.str();
	cout<< "MENSAJE DSET: " <<tmp<<endl;
    pData=(unsigned char*)&tmp[0u];
    return pData;
}



unsigned char *dHeap::makedStatus(){
    unsigned char word[] = "d_status:";
    unsigned char *data;
    std::stringstream ss;
    for(int i = CERO; i < sizeof(word)-DOS; i++){
         ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(word[i]);
    }
    std::string temp = ss.str();
    data = (unsigned char*)&temp[0u];
    return data;
}



/**
 * @brief dHeap::makeIp
 * @param pIp
 * @return
 */
unsigned char* dHeap::makeIp(std::string pIp){
    unsigned char* ip = new unsigned char [CUATRO];
    int index=CERO;
    for(int i=CERO;i<pIp.length(); i+=CUATRO){
        std::string token = pIp.substr(i,TRES);
        ip[index]=std::stoi(token);
        index++;
    }
    return ip;
}



unsigned char* dHeap::makedFree(unsigned char *word, unsigned char *ip, unsigned char *port, unsigned char *pMem, unsigned char *pBytes){
    unsigned char* pData;
    std::stringstream ss;
        ss << word;
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(ip[i]);
    for(int i=CERO; i<DOS;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(port[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(pMem[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(pBytes[i]);
    std::string tmp=ss.str();
    cout<<tmp<<endl;
    pData=(unsigned char*)&tmp[0u];
    return pData;
}



unsigned char* dHeap::makedGet(unsigned char *word, unsigned char *ip, unsigned char *port, unsigned char *pMem, unsigned char *pBytes){
    unsigned char* pData;
    std::stringstream ss;
        ss << word;
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(ip[i]);
    for(int i=CERO; i<DOS;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(port[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(pMem[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(pBytes[i]);
    std::string tmp=ss.str();
    cout<< "MENSAJE DGET: " <<tmp<<endl;
    pData=(unsigned char*)&tmp[0u];
    return pData;
}



unsigned int dHeap::addressInSDS(unsigned int pAddressHeap){
    Node_LL *tmp=((LinkedList*)listaDeServidores)->getHead();
    //pthread_mutex_t mutexTemporal = tmp->getMutex();
    unsigned int _inicial = tmp->getInicio();
    unsigned int _final = tmp->getFinal();
    unsigned int _result = 0;

    while(tmp !=NULL){
        if(_inicial <= pAddressHeap && _final >= pAddressHeap){
            _result = pAddressHeap-tmp->getInicio();
            break;
        }
        tmp = tmp->getNext();
        //pthread_mutex_lock(&mutexTemporal);
    }
}



/**
 * @brief dHeap::~dHeap Destructor por defecto
 * de nuestra clase.
 */
dHeap::~dHeap()
{

}
