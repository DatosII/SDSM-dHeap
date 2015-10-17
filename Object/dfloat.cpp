#include "Object/dfloat.h"

/**
 * @brief Constructor de la clase dFloat
 *
 * Cuando se instancia un nuevo dFloat, se crea un d_pointer_size_type
 * llamando al método dMalloc del dHeap, el cual reserva el espacio
 * de un float(4 bytes) en alguno de los SDSMNode que se encuentren
 * conectados, luego se asigna al dFloat el ID del d_pointer_size_type
 * creado, lo cual permitira buscar el d_pointer dentro de la lista de
 * metadatos
 */
dFloat::dFloat(){
    dObjectType='F';
	this->_id = 0;
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = heap->dMalloc(INT_SIZE,'F');
	this->_id = myPointer->getID();
}



/**
 * @brief Sobrecarga del operador =
 *
 * Llama al método dSet del dHeap para conectarse al SDSMNode donde
 * el d_pointer_size_type del objeto reservo el espacio, y envia el
 * mensaje para guardar dentro de este espacio, el numero que se le
 * asigno al dFloat
 *
 * @param pFloat Valor del dInt
 */
void dFloat::operator =(float pFloat){
	dHeap *heap = dHeap::instancia();
	unsigned char *numBytes = heap->intToBytes(INT_SIZE);
	unsigned char *byteStream = heap->floatToBytes(pFloat);
	d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);
	unsigned char* status = heap->dSet(myPointer, numBytes, byteStream);
    if(*status == 1) std::cout << "NO SE REALIZO EL SET" << "\n";
    delete numBytes, byteStream;
}



float dFloat::operator *(){
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
    else  return *(float*)status;
}
