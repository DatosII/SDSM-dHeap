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
        std::cout << MSGWELCOME << std::endl;
        std::getline (std::cin , choice);
    }
    while( (choice != INSERT) && (choice != DELETE) && (choice != FORMAT) && (choice != GET) && (choice != EXIT));
    if(choice== INSERT){
        insertData();
    }
    else if (choice == DELETE){
        deleteData();
    }
    else if (choice == FORMAT){
        formatData();
    }
    else if (choice == GET){
        getData();
    }
    else if (choice== EXIT)
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
        std::cout << MSGINSERTTYPEDATA << std::endl;
        std::getline (std::cin , type);
    }
    while( (type != CHAR) && (type != STRING) && (type != FLOAT) && (type != INT) );
    std::cout << MSGINSERTDATA << std::endl;
    std::getline (std::cin , pdata);
    if (type == CHAR){
        char data;
        try{
            data = boost::lexical_cast<char>(pdata);
            dChar *myChar = new dChar();
            *myChar=data;
            this->listData->insertData(new NodoApp(myChar));
            std::cout << MSGINSERT << myChar->getID() << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
    }
    else if (type == STRING){
        dString *myString = new dString();
        *myString = pdata;
        this->listData->insertData(new NodoApp(myString));
        std::cout << MSGINSERT << myString->getID() << std::endl;
    }
    else if ( type == FLOAT){
        float data;
        try{
            data = boost::lexical_cast<float>(pdata);
            dFloat *myFloat = new dFloat();
            *myFloat = data;
            this->listData->insertData(new NodoApp(myFloat));
            std::cout << MSGINSERT << myFloat->getID() << std::endl;
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
            std::cout << MSGINSERT << myInt->getID() << std::endl;
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
    std::cout << MSGID << std::endl;
    std::getline (std::cin , pdata);
    unsigned int data;
    try{
            data = boost::lexical_cast<unsigned int>(pdata);
            NodoApp *temp = this->listData->find(data);
            if (temp!=NULL){
                temp->getData()->deleteData();
                this->listData->remove(data);
                std::cout <<  MSGDELETE << std::endl;
            }
            else
                std::cout <<  MSGDATADONTEXISTS << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
}
/**
 * @brief App::getData, obtiene un dato
 *  Este metodo permite obtener un dato solicitado a partir del id
 */
void App::getData(){
    std::cout << MSGID << std::endl;
    std::getline (std::cin , pdata);
    unsigned int data;
    try{
            data = boost::lexical_cast<unsigned int>(pdata);
            NodoApp *temp = this->listData->find(data);
            if (temp!=NULL){
                if(temp->getData()->getDObjectType()=='C')
                    std::cout << MSGGETDATA << **(dChar*)temp->getData() << std::endl;
                else if(temp->getData()->getDObjectType()=='S')
                    std::cout << MSGGETDATA << **(dString*)temp->getData() << std::endl;
                else if(temp->getData()->getDObjectType()=='F')
                    std::cout << MSGGETDATA << **(dFloat*)temp->getData() << std::endl;
                else
                    std::cout << MSGGETDATA << **(dInt*)temp->getData() << std::endl;
            }
            else
                std::cout <<  MSGDATADONTEXISTS << std::endl;
        }
        catch(boost::bad_lexical_cast & e){
            std::cout << e.what() << std::endl;
        }
}

/**
 * @brief App::formatData, Elimina todos los datos
 * Este metodo se encarga de eliminar todos los elementos
 */
void App::formatData(){
    this->listData->format();
    std::cout << MSGFORMATDATA << std::endl;
}
