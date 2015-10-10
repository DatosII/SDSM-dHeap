#ifndef D_POINTER_SIZE_TYPE_H
#define D_POINTER_SIZE_TYPE_H

#include <cstdlib>
//#include "dobject.h"
//#include "dint.h"
//#include "dchar.h"
//#include "dstring.h"
//#include "dfloat.h"

#define CERO 0

class d_pointer_size_type{

private:
    static unsigned int _id;
    unsigned int ID;
    unsigned int _ptr;
    unsigned int _space;
    unsigned char _type;
    unsigned char _ref;
    unsigned char* _ip;
    short _puerto;

public:

    d_pointer_size_type();
    int getID()const;
    int getPtr()const;
    int getSpace();
    char getType();
    char getRef();
    void setID(int pID);
    void setPtr(int pPtr);
    void setSpace(int pSpace);
    void setType(char pType);
    void setRef(char pRef);
    short getPuerto();
    void setPuerto(short pPuerto);

    unsigned char* getIp();
    void setIp(unsigned char *pIp);

    bool operator== (const d_pointer_size_type &pPointer);
    void operator= (const d_pointer_size_type &pPointer);
//    dObject& operator *();
//    dObject* operator ->();
    //incompleto
//    void operator= (const dObject &pdObject);
};

#endif // D_POINTER_SIZE_TYPE_H
