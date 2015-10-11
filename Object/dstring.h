#ifndef DSTRING
#define DSTRING

#include "Object/dobject.h"
#include <iostream>

class dString: public dObject {

public:
	dString(); //Constructor
	~dString(); //Destructor

	void operator=(std::string pString); //Sobrecargar operador =
	std::string operator*(); //Sobrecarga operador *
	};


#endif // DSTRING

