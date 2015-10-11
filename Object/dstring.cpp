#include "Object/dstring.h"

/**
 * @brief Constructor de la clase dString
 *
 */
dString::dString(){
	this->_id = 0;
}



/**
 * @brief Sobrecarga del operador =
 *
 * Llama al método dMalloc del dHeap, el cual reserva el espacio de memoria
 * en alguno de los SDSMNode conectados, luego se llama al método dSet, el
 * cual envia el mensaje con el String que se quiere almacenar en el espacio
 * reservado
 *
 * @param pString Valor del dString
 */
void dString::operator =(std::string pString){
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = heap->dMalloc(pString.length(), 'S');
	this->_id = myPointer->getID();
	unsigned char *numBytes = heap->intToBytes(pString.length());
	unsigned char *byteStream = heap->stringToBytes(pString);
	unsigned char* status = heap->dSet(myPointer, numBytes, byteStream);
	delete numBytes, byteStream;
}



std::string dString::operator *(){
	dHeap *heap = dHeap::instancia();
	d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);

}
