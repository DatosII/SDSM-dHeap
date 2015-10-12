#include "Object/dobject.h"

/**
 * @brief Constructor de la clase
 */
dObject::dObject(){

}


/**
 * @brief Método para obtener el tipo de dato
 *
 * @return Tipo de dato
 */
char dObject::getDObjectType(){
	return dObjectType;
}


/**
 * @brief Método para establecer el tipo de dato
 *
 * @param pType Tipo de dato
 */
void dObject::setDObjectType(char pType){
	this->dObjectType = pType;
}


/**
 * @brief Método para asignar e id del d_pointer
 *
 * @param pId Id del d_pointer
 */
void dObject::setID(unsigned int pId){
	this->_id = pId;
}



d_pointer_size_type *dObject::getdPointer(){
    dHeap *heap = dHeap::instancia();
    d_pointer_size_type *myPointer = ((LinkedListMD*)heap->getListaMD())->findByID(_id);
    return myPointer;
}


void dObject::deleteData(){
    dHeap *heap = dHeap::instancia();
    heap->dFree(this->getdPointer());

}










