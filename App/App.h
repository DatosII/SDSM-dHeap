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


class  App
{
private:
    std::string pdata;
    std::string choice;
    std::string type;
    std::string pString= "string";
    std::string pInt= "int";
    std::string pChar= "char";
    std::string pFloat= "float";
    std::string pExit= "exit";
    std::string pInsert= "insert";
    std::string pDelete= "delete";
    std::string pFormat= "format";
    std::string pMsgWelcome = "Enter your choice, between insert, delete, format or exit: ";
    std::string pMsgInsertTypeData= "Now, enter the type of the data, between char, string, float or int: ";
    std::string pMsgInsertData= "Now, write your data:";
    std::string pMsgInsert= "Your data are inserted";
    std::string pMsgDeleteData= "Now, insert the data to delete:";
    std::string pMsgDelete= "Your data are deleted";
    std::string pMsgFormat= "All data are deleted" ;
    ListaApp *listData;
    void insertData();
    void deleteData();
public:
    App();
    void solicitud();
};

#endif // APP_H
