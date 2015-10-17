#ifndef APP_H
#define APP_H

#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <boost/lexical_cast.hpp>
#include "Object/dint.h"
#include "Object/dchar.h"
#include "Object/dfloat.h"
#include "Object/dstring.h"
#include "listaapp.h"
#include "nodoapp.h"

#define STRING "string"
#define INT "int"
#define CHAR "char"
#define FLOAT "float"
#define INSERT "insert"
#define DELETE "delete"
#define FORMAT "format"
#define GET "get"
#define EXIT "exit"
#define MSGWELCOME "Enter your choice, between insert, delete, format, get or exit: "
#define MSGINSERTTYPEDATA "Now, enter the type of the data, between char, string, float or int: "
#define MSGINSERTDATA "Now, write your data:"
#define MSGINSERT "Your data are inserted, and the data id is: "
#define MSGID "Now, insert the data id: "
#define MSGDELETE "Your data are deleted"
#define MSGFORMATDATA "All data are deleted"
#define MSGDATADONTEXISTS "Don't exist any data with this id"
#define MSGGETDATA "Your Data is: "

/**
 * @fiee
 * @brief The App class
 */
class  App{
private:
    std::string pdata;
    std::string choice;
    std::string type;
    ListaApp *listData;
    void insertData();
    void deleteData();
    void formatData();
    void getData();

public:
    App();
    void solicitud();
};

#endif // APP_H
