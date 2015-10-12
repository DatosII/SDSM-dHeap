#include "Object/dchar.h"

/**
 * @brief Constructor de la clase dInt
 *
 * Cuando se instancia un nuevo dChar, se crea un d_pointer_size_type
 * llamando al método dMalloc del dHeap, el cual reserva el espacio
 * de un char(1 byte) en alguno de los SDSMNode que se encuentren
 * conectados, luego se asigna al dChar el ID del d_pointer_size_type
 * creado, lo cual permitira buscar el d_pointer dentro de la lista de
 * metadatos
 */
dChar::dChar(){
	this->_id = 0;
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = heap->dMalloc(CHAR_SIZE,'C');
	this->_id = myPointer->getID();
}

/**
 * @brief Sobrecarga del operador =
 *
 * Llama al método dSet del dHeap para conectarse al SDSMNode donde
 * el d_pointer_size_type del objeto reservo el espacio, y envia el
 * mensaje para guardar dentro de este espacio, el char que se le
 * asigno al dChar
 *
 * @param pChar Valor del dInt
 */
void dChar::operator =(const unsigned char pChar){
	dHeap *heap = dHeap::instancia();
	unsigned char *numBytes = heap->intToBytes(CHAR_SIZE);
	unsigned char charTemp = (unsigned char)pChar;
	unsigned char *ptrTemp = &charTemp;
	d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);
	unsigned char* status = heap->dSet(myPointer, numBytes, ptrTemp);
    if(*status == 1) std::cout << "NO SE REALIZO EL SET" << "\n";
    delete numBytes;
}



unsigned char dChar::operator *(){
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);
    unsigned char *numBytes = heap->intToBytes(CHAR_SIZE);
    unsigned int _realAddress = heap->addressInSDS(myPointer->getPtr());
    unsigned char *bytesAddress = heap->intToBytes(_realAddress);
    unsigned char *status = heap->dGet(myPointer, numBytes, bytesAddress);
    delete numBytes, bytesAddress;
    if(status == NULL){
        std::cout << "NO SE PUDO OBTENER EL DATO" << std::endl;
        return 0;
    }
    else  return *(unsigned char*)status;
}

