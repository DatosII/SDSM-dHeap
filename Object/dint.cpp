#include "Object/dint.h"

/**
 * @brief Constructor de la clase dInt
 *
 * Cuando se instancia un nuevo dInt, se crea un d_pointer_size_type
 * llamando al método dMalloc del dHeap, el cual reserva el espacio
 * de un int(4 bytes) en alguno de los SDSMNode que se encuentren
 * conectados, luego se asigna al dInt el ID del d_pointer_size_type
 * creado, lo cual permitira buscar el d_pointer dentro de la lista de
 * metadatos
 */
dInt::dInt(){
    dObjectType='I';
	this->_id = 0;
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = heap->dMalloc(INT_SIZE,'I');
	this->_id = myPointer->getID();
}



/**
 * @brief Sobrecarga del operador =
 *
 * Llama al método dSet del dHeap para conectarse al SDSMNode donde
 * el d_pointer_size_type del objeto reservo el espacio, y envia el
 * mensaje para guardar dentro de este espacio, el numero que se le
 * asigno al dInt
 *
 * @param pInt Valor del dInt
 */
void dInt::operator =(const unsigned int pInt){
	dHeap *heap = dHeap::instancia();
	unsigned char *numBytes = heap->intToBytes(INT_SIZE);
	unsigned char *byteStream = heap->intToBytes(pInt);
	d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);
	unsigned char* status = heap->dSet(myPointer, numBytes, byteStream);
	if(*status == 1) std::cout << "NO SE REALIZO EL SET" << "\n";
	delete numBytes, byteStream;
}

unsigned int dInt::operator *(){
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);
    unsigned char *numBytes = heap->intToBytes(INT_SIZE);
    unsigned int _realAddress = heap->addressInSDS(myPointer->getPtr());
    unsigned char *bytesAddress = heap->intToBytes(_realAddress);
    unsigned char *status = heap->dGet(myPointer, numBytes, bytesAddress);
    delete numBytes, bytesAddress;
    if(status == NULL){
        std::cout << "NO SE PUDO OBTENER EL DATO" << std::endl;
        return 0;
    }
    else  return *(unsigned int*)status;
}
