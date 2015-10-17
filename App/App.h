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

#define pString "string"
#define pInt "int"
#define pChar "char"
#define pFloat "float"
#define pInsert "insert"
#define pDelete "delete"
#define pFormat "format"
#define pGet "get"
#define pExit "exit"
#define pMsgWelcome "Enter your choice, between insert, delete, format, get or exit: "
#define pMsgInsertTypeData "Now, enter the type of the data, between char, string, float or int: "
#define pMsgInsertData "Now, write your data:"
#define pMsgInsert "Your data are inserted, and the data id is: "
#define pMsgId "Now, insert the data id: "
#define pMsgDelete "Your data are deleted"
#define pMsgFormatData "All data are deleted"
#define pMsgDataDontExist "Don't exist any data with this id"
#define pMsgGetData "Your Data is: "


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
