#ifndef DOBJECT
#define DOBJECT

#include "Pointer/d_pointer_size_type.h"
#include "Heap/dheap.h"
#include "Listas/linkedlistmd.h"
#include <iostream>

#define INT_SIZE 4
#define CHAR_SIZE 1

class dObject{
protected:
	unsigned int _id;
private:

	char dObjectType;
	void* dObjectPuntData;

public:
	dObject();

	char getDObjectType();
	void setDObjectType(char pType);

	void *getDObjectPuntData();
	void setDObjectPuntData(void *pPuntData);

	void setID(unsigned int pId); //Método para asignar el id del d_pointer
	unsigned int getID(); //Método para obtener el id del d_pointer

	};

#endif // DOBJECT

