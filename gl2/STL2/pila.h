#ifndef PILA_H
#define PILA_H

#include"lista.h"

template<class tipoDato>
class pila:public lista<tipoDato>{
	public:
	void pop(){
		this->borrar(0);
	}
	void push(tipoDato elem){
		this->insertar(0,elem);
	}
	tipoDato top(){
		return this->operator[](0);
	}
};

#endif