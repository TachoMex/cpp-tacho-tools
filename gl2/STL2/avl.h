#ifndef NULL
#define NULL 0
#endif
#ifndef AVL_H
#define AVL_H
template<class T>
class nodoAVL{
	public:
		T dato;
		int factor;
		int tam;
		nodoAVL<T> *izq, *der;
		bool borrado;
		
		nodoAVL(){
			dato=T();
			izq=der=NULL;
			factor=0;
			tam=0;
			borrado=false;
		}
}; 

template<class T>
class AVL{

	
	private:
		void rotacionDD(nodoAVL<T> *& aux){
			nodoAVL<T> *A, *B;
		
			A=aux;
			B=aux->der;
			A->der=B->izq;
			aux=B;
			aux->izq=A;
			
			int tamIzq=(aux->izq->izq?aux->izq->izq->tam+1:0);
			int tamDer=(aux->izq->der?aux->izq->der->tam+1:0);
			aux->izq->tam=(tamIzq>tamDer?tamIzq:tamDer);
			aux->izq->factor=tamDer-tamIzq;
			
			tamIzq=(aux->izq?aux->izq->tam+1:0);
			tamDer=(aux->der?aux->der->tam+1:0);
			aux->tam=(tamIzq>tamDer?tamIzq:tamDer);
			aux->factor=tamDer-tamIzq;
			
		}
		
		void rotacionII(nodoAVL<T>*& aux){
			nodoAVL<T> *A, *B;
			
			
			A=aux;
			B=aux->izq;		
			A->izq=B->der;
			aux=B;
			aux->der=A;
			
			int tamIzq=(aux->der->izq?aux->der->izq->tam+1:0);
			int tamDer=(aux->der->der?aux->der->der->tam+1:0);
			aux->der->tam=(tamIzq>tamDer?tamIzq:tamDer);
			aux->der->factor=tamDer-tamIzq;
			
			tamIzq=(aux->izq?aux->izq->tam+1:0);
			tamDer=(aux->der?aux->der->tam+1:0);
			aux->tam=(tamIzq>tamDer?tamIzq:tamDer);
			aux->factor=tamDer-tamIzq;
			
		}
		
		void rotacionDI(nodoAVL<T>*& aux){
			nodoAVL<T>  *B, *C;
			B=aux->der;
			C=B->izq;	
			aux->der=C;
			C->der=B;
			B->izq=NULL;
			B->tam=0;
			B->factor=0;
			C->tam=1;
			C->factor=1;
			rotacionDD(aux);
				
		}
		
		void rotacionID(nodoAVL<T>*& aux){
			nodoAVL<T> *A, *B, *C;
			B=aux->izq;
			C=B->der;
			aux->izq=C;
			C->izq=B;
			B->der=NULL;
			B->tam=0;
			B->factor=0;
			C->tam=1;
			C->factor=-1;
			rotacionII(aux);
		}

		void balancear(nodoAVL<T>*&aux){
			int tamIzq=(aux->izq?aux->izq->tam+1:0);
			int tamDer=(aux->der?aux->der->tam+1:0);
			aux->tam=(tamIzq>tamDer?tamIzq:tamDer);
			aux->factor=tamDer-tamIzq;
			switch(aux->factor){
				case -2: 
					if(aux->izq->factor==-1){
						rotacionII(aux);
					}
					else{
						rotacionID(aux);
					}
					aux->factor=0;
				break;
					
				case 2:
					if(aux->der->factor==1){
						rotacionDD(aux);
					}
					else{
						rotacionDI(aux);
					}
					aux->factor=0;
				break;
			}
		}

		void insertar(T elem, nodoAVL<T>*& aux){
			if(aux==NULL){
				this->cantElem++;
				aux=new nodoAVL<T>();
				aux->borrado=false;
				aux->dato=elem;
				return;
			}else if(elem < aux->dato){
				insertar(elem, aux->izq);
				
			}else{
				insertar(elem, aux->der);			
			}
			balancear(aux);
		}
		
		bool buscar(T elem, nodoAVL<T>*& aux){
			if(aux==NULL)
				return false;
			if(aux->dato==elem)
				return true;
			if(elem<aux->dato)
				return buscar(elem, aux->izq);
			return buscar(elem, aux->der);		
		}
		
#ifdef DICCIONARIO_H
	public:
		T& buscar2(T& elem, nodoAVL<T>*& aux){
			if(aux==NULL){
				aux=new nodoAVL<T>();
				return aux->dato;
			}
			
			if(elem < aux->dato){
				return buscar2(elem, aux->izq);
			}else if(aux->dato < elem)
				return buscar2(elem, aux->der);
			else
				return aux->dato;
		}
	private:
#endif
		
		void eliminar(T elem, nodoAVL<T>*& aux){
			if(aux==NULL)
				return;
			if(elem==aux->dato){
				if(aux->izq==NULL and aux->der==NULL){
					this->cantElem--;
					delete aux;
					aux=NULL;
				}else if(aux->izq==NULL or aux->der==NULL){
					this->cantElem--;
					nodoAVL<T>* aux2=aux;
					aux=(aux->izq==NULL?aux->der:aux->izq);
					delete aux2;
				}else{
					nodoAVL<T>* aux2=aux->der;
					while(aux2->izq!=NULL)
						aux2=aux2->izq;
					T t=aux2->dato;
					eliminar(t, raiz);
					aux->dato=t;
					
				}
			}else if(elem<aux->dato){
				eliminar(elem, aux->izq);
				balancear(aux);
			}else{
				eliminar(elem, aux->der);
				balancear(aux);
			}
		}
		
		void foreach(void(*proc)(T), nodoAVL<T> *aux){
			if(aux==NULL)
				return;
			foreach(proc, aux->izq);
			proc(aux->dato);
			foreach(proc, aux->der);
		}
	
	public:
		nodoAVL<T> * raiz;
		int cantElem;
	
		AVL(){
			raiz=NULL;
			cantElem=0;
		}
		
		void insertar(T elem){
			insertar(elem, raiz);
		}
		
		bool buscar(T elem){
			buscar(elem, raiz);
		}
		
		int tam(){
			return cantElem;
		}
		
		bool vacio(){
			return cantElem==0;
		}
		
		void eliminar(T elem){
			eliminar(elem, raiz);
		}
		
		void operator+=(T elem){
			insertar(elem, raiz);
		}		
		
		void foreach(void(*proc)(T)){
			foreach(proc, raiz);
		}
};

#endif


