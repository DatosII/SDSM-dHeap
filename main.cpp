#include <string>
#include <string.h>
#include <iostream>
#include "Heap/dheap.h"
#include "Listas/linkedlist.h"
#include "Listas/linkedlistmd.h"
#include "/home/jairodaniel_23/SDSM-dHeap/pugixml-1.6/src/pugixml.cpp"
#include "Object/dint.h"

#define SDSCONFIG "SDSConfiguration"
#define SDS "SDS"
#define NODE "Node"
#define IP "IP"
#define PUERTO "Puerto"
#define EMPTY ""
#define GC "GC"
#define FRECUENCY "gc-Frecuency"
#define PATH "/home/jairodaniel_23/SDSM-dHeap/configuracion.xml"

/**
 * @brief getNodes funcion que extrae los nodos que se conectaran al SDSMM. Se insertan en una lista simple.
 * @param pPath La ruta de archivo de configuracion.
 * @param pListaServidores Lista donde seran alamcenados los nodos Clientes.
 */
void getNodes(char* pPath, LinkedList* pListaServidores){
	pugi::xml_document _doc; //Documento donde se carga el archivo
	pugi::xml_parse_result _result;

	_result = _doc.load_file(pPath);

	for(pugi::xml_node _nodo = _doc.child(SDSCONFIG).child(SDS).child(NODE)
		;_nodo;_nodo=_nodo.next_sibling()){

		if ((std::string)_nodo.child_value(IP)!=EMPTY && (std::string)_nodo.child_value(PUERTO)!= EMPTY){
			std::cout<<(std::string)_nodo.child_value("IP")<<" "+(std::string)_nodo.child_value("Puerto")<<std::endl;
			pListaServidores->insert((std::string)_nodo.child_value(IP), (std::string)_nodo.child_value(PUERTO));
		}
		else
			break;
	}
}

/**
 * @brief getFrecuency Funcion que extraera el tiempo de revision del garbajeCollector
 * @param pPath Es la ruta del archivo de configuracion.
 * @param pListaMetadatos Es lista con los metadatos de la informacion guardada remotamente.
 */
void getFrecuency(char* pPath, LinkedListMD* pListaMetadatos){
	pugi::xml_document _doc; //Documento donde se carga el archivo
	pugi::xml_parse_result _result;

	_result = _doc.load_file(pPath);
	pugi::xml_node _nodo = _doc.child(SDSCONFIG).child(GC);

	pListaMetadatos->iniciarGarbaje((std::string)_nodo.child_value(FRECUENCY));
}

int main(){
	LinkedList* listaCliente = new LinkedList();
	LinkedListMD* listaMetadatos = new LinkedListMD();
	getNodes(PATH,listaCliente);
	getFrecuency(PATH,listaMetadatos);
	dHeap *heap = dHeap::instancia(listaCliente, listaMetadatos);

    dInt *j = new dInt();
    *j = 345;
	dInt *f = new dInt();
    *f=25;
    dInt *h = new dInt();
    *h=5689;

    h->deleteData();

    dInt *m = new dInt();
    *m=567;

//

//

//




	while(true){

	}
	return 0;
}
