#ifndef DFLOAT
#define DFLOAT

#include "Object/dobject.h"
#include <iostream>

/**
 * @file dfloat.h
 * @brief Clase envoltorio para el tipo float
 */

class dFloat: public dObject {

public:
	dFloat(); //Constructor
	~dFloat(); //Destructor

	void operator=(float pFloat); //Sobrecargar operador =
	unsigned int operator*(); //Sobrecarga operador *
	};

#endif // DFLOAT

