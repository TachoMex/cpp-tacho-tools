#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include"avl.h"

template<class L, class T>
class parMAP{
	public:
		T dato;
		L llave;
		template<class K, class D>
		friend bool operator<(parMAP<K, D>,parMAP<K, D>); 
	
};

template<class L, class T>
bool operator<(parMAP<L, T> a,parMAP<L, T> b){
	return a.llave<b.llave;
} 

void prin(parMAP<string, int> i){
	cout<<i.llave<<":"<<i.dato<<endl;
}

template<class L, class T>
class diccionario{
	private:
		AVL< parMAP<L, T> > a;
	
	public:
		T& operator[](L llave){
			parMAP<L, T> m, *aux;
			m.llave=llave;
			aux=&a.buscar2(m, a.raiz);
			aux->llave=llave;
			return aux->dato;
		}
};

#endif