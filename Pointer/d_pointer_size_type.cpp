#include "Pointer/d_pointer_size_type.h"

d_pointer_size_type::d_pointer_size_type(){
    _space = CERO;
//    _object = CERO;
    _ptr= CERO;
//    _object = CERO;
    _type = CERO;
    ID = d_pointer_size_type::_id;
    d_pointer_size_type::_id++;
	setRef(1);
}

unsigned int d_pointer_size_type::_id = CERO;


unsigned int d_pointer_size_type::getID()const{
    return ID;
}


unsigned int d_pointer_size_type::getPtr()const{
    return _ptr;
}


int d_pointer_size_type::getSpace(){
    return _space;
}


char d_pointer_size_type::getType(){
    return _type;
}


int d_pointer_size_type::getRef(){
    return _ref;
}


void d_pointer_size_type::setID(int pID){
    this->ID=pID;
}


void d_pointer_size_type::setPtr(int pPtr){
    this->_ptr=pPtr;
}


void d_pointer_size_type::setSpace(int pSpace){
    this->_space=pSpace;
}


void d_pointer_size_type::setType(char pType){
    this->_type=pType;
}


void d_pointer_size_type::setRef(int pRef){
	this->_ref+=pRef;
	//this->_ref= static_cast<unsigned int>(this->_ref) + static_cast<unsigned int>(pRef);
}


bool d_pointer_size_type::operator== (const d_pointer_size_type &pPointer){
    return (pPointer.getPtr() == this->getPtr());
}


void d_pointer_size_type::operator= (const d_pointer_size_type &pPointer){
    this->setID(pPointer.getID());
}


unsigned char* d_pointer_size_type::getIp(){
    return this->_ip;
}


void d_pointer_size_type::setIp(unsigned char* pIp){
    this->_ip = pIp;
}

short d_pointer_size_type::getPuerto(){
	return this->_puerto;
}

void d_pointer_size_type::setPuerto(short pPuerto){
    this->_puerto = pPuerto;
}


/**
 * @brief Método para asignar los bytes de la ip de la
 * computadora donde posee memoria reservada
 *
 * @param pIp Ip en forma de bytes
 */
void d_pointer_size_type::setIpBytes(unsigned char *pIp){
	this->_ipBytes = pIp;
}


/**
 * @brief Método para obtener los bytes de la ip de la
 * computadora  donde posee memoria reservada
 *
 * @return Ip en forma de bytes
 */
unsigned char *d_pointer_size_type::getIpBytes(){
	return this->_ipBytes;
}


//dObject& d_pointer_size_type::operator*(){
//    return *_object;
//}


//dObject *d_pointer_size_type::operator ->(){
//    return _object;
//}

/*void d_pointer_size_type::operator= (const  dInt &pdInt){
    if(this->getSpace()==pdInt.getSpace())
        this->setRef(1);
    return;
}*/

/*void  d_pointer_size_type::operator =(const int pInt){
    return ;
}*/
