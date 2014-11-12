#ifndef NODO_H
#define NODO_H

template<class tipoElemento>
class nodo{
public:
	nodo<tipoElemento> *siguiente;
	tipoElemento dato;
	nodo(tipoElemento dato);
};


template<class tipoElemento> nodo<tipoElemento>::nodo(tipoElemento dato){
	this->dato=dato;
	siguiente=0;
}

#endif