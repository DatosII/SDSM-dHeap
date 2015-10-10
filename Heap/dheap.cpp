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
 * @brief dHeap::dMalloc
 * @param size
 * @param type
 * @return
 */
d_pointer_size_type* dHeap::dMalloc(unsigned int size, char type){
        d_pointer_size_type*  pointer;
        pointer->setType(type);
        unsigned int address = request(size,pointer);
        pointer->setPtr(address);
        pointer->setSpace(size);
        pointer->setRef('1');
        dHeap *heap = dHeap::instancia();
        ((LinkedListMD*)heap->getListaMD())->insert(pointer);
        return pointer;
}

/**
 * @brief dSet Metodo que envia el dato para ser almacenado en el SDS.
 * @param pPointer es el puntero del que tenemos la informacion.
 */
unsigned char* dHeap::dSet(d_pointer_size_type* pPointer, unsigned char* pBytes, unsigned char* pByStream){
    unsigned char* _ip = pPointer->getIp();
    unsigned char* _puerto = this->shortToBytes((unsigned short)pPointer->getPuerto());

    unsigned char _arreglo[] = DSET;
    unsigned char* ptr = _arreglo;
    unsigned char* _message = this->makedSet(ptr,_ip,_puerto,pBytes,pByStream);

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
        if(nodoDeEnvio->getFlag()==TRES)
			flag = false;
        pthread_mutex_unlock(&mutexTemporal);
    }
    pthread_mutex_lock(&mutexTemporal);
    pData= (unsigned char*)nodoDeEnvio->getMsg();
    nodoDeEnvio->setFlag(CERO);
    pthread_mutex_unlock(&mutexTemporal);
	if(pData[0] == CERO){
        return _ip;
    }
    else{
        return CERO;
    }
}

/**
 * @brief dHeap::dFree
 * @param toFree
 */
void dHeap::dFree(d_pointer_size_type toFree){
   void * pPtr;
    //*pPtr= toFree.getPtr();
   free(pPtr);
}

/**
 * @brief dHeap::request
 * @param size
 * @return
 */
unsigned int dHeap::request(unsigned int size, d_pointer_size_type* pPointer){

    bool loopDel3 = true;

    unsigned char word[] = DCALLOC ;
    unsigned char*  ptrw= word;
    unsigned char *byte = intToBytes(size);
    unsigned char* pData=makedCalloc(ptrw, byte);

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
            pData= (unsigned char*)tmp->getMsg();
            tmp->setFlag(CERO);
            pthread_mutex_unlock(&mutexTemporal);
            if(pData[CERO]==UNO){
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
        return NULL;
    else {
        pPointer->setIp((unsigned char*)tmp->getIP());
        pPointer->setPuerto((short)tmp->getPuerto());
        unsigned char* tmpAdd= pData+UNO;
        unsigned int address = *((unsigned int*)tmpAdd);
        return address+offset;
    }
}

/**
 * @brief dHeap::intToBytes
 * @param pInt
 * @return
 */
unsigned char* dHeap::intToBytes(unsigned int pInt){
    unsigned char* bytes= new unsigned char[CUATRO];
    for (int index = CERO, byte=CERO; index<CUATRO, byte<=TRES; index++, byte++)
        bytes[index]=pInt>>(OCHO*byte)&0xFF;
    return bytes;
}


unsigned char* dHeap::shortToBytes(unsigned short pShort){
	unsigned char* bytes = new unsigned char[DOS];

	bytes[CERO] = (pShort & 0xFF00) >> OCHO;
    bytes[UNO] = pShort & 0x00FF;

	return bytes;
}

/**
 * @brief dHeap::makedCalloc
 * @param pOne
 * @param pTwo
 * @return
 */
unsigned char* dHeap::makedCalloc(unsigned char* pOne, unsigned char* pTwo){
    unsigned char* pData = (unsigned char*)strcat((char*)pOne, (char*)pTwo);
    return pData ;
}

/**
 * @brief dHeap::makedSet
 * @param word
 * @param ip
 * @param port
 * @param bytes
 * @param bystream
 * @return
 */
unsigned char* dHeap::makedSet(unsigned char word[], unsigned char* ip,
                               unsigned char* port, unsigned char* bytes, unsigned char* bystream){

    unsigned char* pData;
    std::stringstream ss;
    for(int i=CERO; i<sizeof(word)-DOS; i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(word[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(ip[i]);
    for(int i=CERO; i<DOS;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(port[i]);
    for(int i=CERO; i<CUATRO;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(bytes[i]);
    unsigned int* numBytes = (unsigned int*)bytes;
    for(int i=CERO; i<*numBytes;i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(bystream[i]);
    std::string tmp=ss.str();
    cout<<tmp<<endl;
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

unsigned char* dHeap::makedFree(unsigned char word[], unsigned char *ip, unsigned char *port, unsigned char *pMem, unsigned char *pBytes){
    unsigned char* pData;
    std::stringstream ss;
    for(int i=CERO; i<sizeof(word)-UNO; i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(word[i]);
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

unsigned char* dHeap::makedGet(unsigned char word[], unsigned char *ip, unsigned char *port, unsigned char *pMem, unsigned char *pBytes){
    unsigned char* pData;
    std::stringstream ss;
    for(int i=CERO; i<sizeof(word)-DOS; i++)
        ss<<std::setfill('0')<<std::setw(DOS)<<std::hex<<static_cast<unsigned int>(word[i]);
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
/**
 * @brief dHeap::~dHeap Destructor por defecto
 * de nuestra clase.
 */
dHeap::~dHeap()
{

}
