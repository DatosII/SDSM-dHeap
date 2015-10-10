#include "Pointer/d_pointer_size_type.h"

d_pointer_size_type::d_pointer_size_type(){
    _space = CERO;
//    _object = CERO;
    _ptr= CERO;
//    _object = CERO;
    _type = CERO;
    ID = d_pointer_size_type::_id;
    d_pointer_size_type::_id++;
    setRef('1');
}

unsigned int d_pointer_size_type::_id = CERO;


int d_pointer_size_type::getID()const{
    return ID;
}


int d_pointer_size_type::getPtr()const{
    return _ptr;
}


int d_pointer_size_type::getSpace(){
    return _space;
}


char d_pointer_size_type::getType(){
    return _type;
}


char d_pointer_size_type::getRef(){
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
    switch(pType){
//    case 'I': _object = new dInt(); break;
//    case 'C': _object = new dChar(); break;
//    case 'S': _object = new dString(); break;
//    case 'F': _object = new dFloat(); break;
    }
}


void d_pointer_size_type::setRef(char pRef){
    this->_ref= static_cast<unsigned int>(this->_ref) + static_cast<unsigned int>(pRef);
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
