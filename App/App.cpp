#include "App.h"
/**
 * @brief App::App, constructor de la clase
 */
App::App(){
    this->listData = new ListaApp();
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
        std::cout << pMsgWelcome << std::endl;
        std::getline (std::cin , choice);
    }
    while( (choice != pInsert) && (choice != pDelete) && (choice != pFormat) && (choice != pGet) && (choice != pExit));
    if(choice== pInsert){
        insertData();
    }
    else if (choice == pDelete){
        deleteData();
    }
    else if (choice == pFormat){
        formatData();
    }
    else if (choice == pGet){
        getData();
    }
    else if (choice== pExit)
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
        std::cout << pMsgInsertTypeData << std::endl;
        std::getline (std::cin , type);
    }
    while( (type != pChar) && (type != pString) && (type != pFloat) && (type != pInt) );
    std::cout << pMsgInsertData << std::endl;
    std::getline (std::cin , pdata);
    if (type == pChar){
        char data;
        try{
            data = boost::lexical_cast<char>(pdata);
            dChar *myChar = new dChar();
            *myChar=data;
            this->listData->insertData(new NodoApp(myChar));
            std::cout << pMsgInsert << myChar->getID() << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
    else if (type == pString){
        dString *myString = new dString();
        *myString = pdata;
        this->listData->insertData(new NodoApp(myString));
        std::cout << pMsgInsert << myString->getID() << std::endl;
    }
    else if ( type == pFloat){
        float data;
        try{
            data = boost::lexical_cast<float>(pdata);
            dFloat *myFloat = new dFloat();
            *myFloat = data;
            this->listData->insertData(new NodoApp(myFloat));
            std::cout << pMsgInsert << myFloat->getID() << std::endl;
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
            this->listData->insertData(new NodoApp(myInt));
            std::cout << pMsgInsert << myInt->getID() << std::endl;
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
    std::cout << pMsgId << std::endl;
    std::getline (std::cin , pdata);
    unsigned int data;
    try{
            data = boost::lexical_cast<unsigned int>(pdata);
            NodoApp *temp = this->listData->find(data);
            if (temp!=NULL){
                temp->getData()->deleteData();
                this->listData->remove(data);
                std::cout <<  pMsgDelete << std::endl;
            }
            else
                std::cout <<  pMsgDataDontExist << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
}

void App::getData(){
    std::cout << pMsgId << std::endl;
    std::getline (std::cin , pdata);
    unsigned int data;
    try{
            data = boost::lexical_cast<unsigned int>(pdata);
            NodoApp *temp = this->listData->find(data);
            if (temp!=NULL){
                if(temp->getData()->getDObjectType()=='C')
                    std::cout << pMsgGetData << **(dChar*)temp->getData() << std::endl;
                else if(temp->getData()->getDObjectType()=='S')
                    std::cout << pMsgGetData << **(dString*)temp->getData() << std::endl;
                else if(temp->getData()->getDObjectType()=='F')
                    std::cout << pMsgGetData << **(dFloat*)temp->getData() << std::endl;
                else
                    std::cout << pMsgGetData << **(dInt*)temp->getData() << std::endl;
            }
            else
                std::cout <<  pMsgDataDontExist << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
}


void App::formatData(){
    this->listData->format();
    std::cout << pMsgFormatData << std::endl;
}
