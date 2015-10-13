#include "App.h"
/**
 * @brief App::App, constructor de la clase
 */
App::App()
{
}

/**
 * @brief App::solicitud, solicitud de los datos
 * Este metodo se encarga de solicitar y llevar acabo lo deseado
 * por el usuario
 * @see insertData()
 * @see deleteData
 */
void App::solicitud(){
    do{
        std::cout << this->pMsgWelcome << std::endl;
        std::getline (std::cin , choice);
    }
    while( (choice != this->pInsert) && (choice != this->pDelete) && (choice != this->pFormat) && (choice != this->pExit));
    if(choice==this->pInsert){
        insertData();
    }
    else if (choice == this->pDelete){
        deleteData();
    }
    else if (choice == this->pFormat){
            std::cout << this->pMsgFormat << std::endl;;
    }
    else if (choice== this->pExit)
        exit(0);
    solicitud();
}
/**
 * @brief App::insertData, inserta los datos
 * Este método se encarga del casteo y la inserción de los
 * datos ingresados
 */
void App::insertData(){
    do{
        std::cout << this->pMsgInsertTypeData << std::endl;
        std::getline (std::cin , type);
    }
    while( (type != this->pChar) && (type != this->pString) && (type != this->pFloat) && (type != pInt) );
    std::cout << this->pMsgInsertData << std::endl;
    std::getline (std::cin , pdata);
    if (type == this->pChar){
        char data;
        try{
            data = boost::lexical_cast<char>(pdata);
            dChar *myChar = new dChar();
            *myChar=data;
            std::cout << this->pMsgInsert << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
    else if (type == this->pString){
        dString *myString = new dString();
        *myString = pdata;
        std::cout << this->pMsgInsert << std::endl;
    }
    else if ( type == this->pFloat){
        float data;
        try{
            data = boost::lexical_cast<float>(pdata);
            dFloat *myFloat = new dFloat();
            *myFloat = data;
            std::cout << this->pMsgInsert << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
    else{
        int data;
        try{
            data = boost::lexical_cast<int>(pdata);
            dInt *myInt = new dInt();
            *myInt = data;
            std::cout << this->pMsgInsert << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
}



/**
 * @brief App::deleteData, elimina los datos
 * Este método se encarga del casteo y la eliminación de los
 * datos solicitados
 */
void App::deleteData(){
    do{
        std::cout << this->pMsgInsertTypeData << std::endl;
        std::getline (std::cin , type);
    }
    while( (type != this->pChar) && (type != this->pString) && (type != this->pFloat) && (type != this->pInt) );
    std::cout << this->pMsgDeleteData << std::endl;
    std::getline (std::cin , pdata);
    if (type == this->pChar){
        char data;
        try{
            data = boost::lexical_cast<char>(pdata);
            // delete dato
            std::cout << this->pMsgDelete << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
    else if (type == this->pString){
        //delete dato
        std::cout << this->pMsgDelete << std::endl;
    }
    else if (type == this->pFloat){
        float data;
        try{
            data = boost::lexical_cast<float>(pdata);
            //delete dato
            std::cout << this->pMsgDelete << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
    else{
        int data;
        try{
            data = boost::lexical_cast<int>(pdata);
            // delete dato
            std::cout << this->pMsgDelete << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }

}
