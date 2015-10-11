#ifndef DCHAR
#define DCHAR

#include "Object/dobject.h"
#include <iostream>

/**
 * @file dchar.h
 * @brief Clase envoltorio para el tipo char
 */

class dChar: public dObject{

public:
	dChar(); //Constructor
	~dChar(); //Destructor

	void operator=(const unsigned char pChar); //Sobrecarga operador =
	unsigned char operator *(); //Sobrecargar operador *
	};

#endif // DCHAR

