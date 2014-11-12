#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

#define null 0
#define NOT_FOUND 404

template<class tipoElemento>
class lista{
	private:
		int cantidadElementos;
		nodo<tipoElemento> *cabecera;
	
	public:
		lista<tipoElemento>(){
			cantidadElementos=0;
			cabecera=new nodo<tipoElemento>(tipoElemento());
		}
	
		void operator+=(tipoElemento dato){
			nodo<tipoElemento> *actual;
			actual=cabecera;
			while(actual->siguiente!=null)
				actual=actual->siguiente;
			actual->siguiente= new nodo<tipoElemento>(dato);
			cantidadElementos++;
		}

		void operator+=(lista<tipoElemento> l){
			nodo<tipoElemento> *aux = cabecera;
			while(aux->siguiente != null)
				aux = aux->siguiente;
			aux->siguiente = l.cabecera->siguiente;
			cantidadElementos += l.cantidadElementos;
		}

		void agregar(tipoElemento dato){
			*(this)+=dato;
		}
		
		tipoElemento& operator[](int n){
			nodo<tipoElemento> *actual=cabecera;
			for(int i=0;i<=n;i++)
				if(actual==null)
					throw(NOT_FOUND);
				else
					actual=actual->siguiente;
			return actual->dato;
		}
		
		int tam(){
			return cantidadElementos;
		}
		
		void borrar(int n){
			if(n<0) 
				return;
			nodo<tipoElemento> *actual=cabecera;
			for(int i=0;i<n;i++)
				if(actual==null)
					return;
				else
					actual=actual->siguiente;
			nodo<tipoElemento> *aux=actual->siguiente;
			actual->siguiente=actual->siguiente->siguiente;
			cantidadElementos--;
			delete aux;
		}
		
		bool vacia(){
			return cantidadElementos==0;
		}

		void reiniciar(){
			while(!vacia()){
				borrar(0);
			}
		}
		void insertar(int n, tipoElemento dato){
			if(n<0) 
				return;
			nodo<tipoElemento> *actual=cabecera;
			for(int i=0;i<n-1;i++){
				if(actual==null)
					return;
				actual=actual->siguiente;
			}
			nodo<tipoElemento> *nuevo=new nodo<tipoElemento>(dato);
			nuevo->siguiente=actual->siguiente;
			actual->siguiente=nuevo;
			cantidadElementos++;
			
		}
};
#endif