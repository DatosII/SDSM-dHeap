#ifndef DINT
#define DINT

#include "Object/dobject.h"
#include <iostream>

/**
 * @file dint.h
 * @brief Clase envoltorio para el tipo int
 */

class dInt: public dObject {

public:
	dInt(); //Constructor
	~dInt(); //Destructor

	void operator=(const unsigned int pInt); //Sobrecargar operador =
	unsigned int operator*(); //Sobrecarga operador *
	};

#endif // DINT

