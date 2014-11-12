#include<cstdio>

class nodoAVL{
	public:
		int dato;
		int factor;
		int tam;
		nodoAVL *izq, *der;
		
		nodoAVL(){
			dato=0;
			izq=der=NULL;
			factor=0;
			tam=0;
		}
}; 

class AVL{
	public:
		void rotacionDD(nodoAVL *& aux){
			nodoAVL *A, *B;
		
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
		
		void rotacionII(nodoAVL*& aux){
			nodoAVL *A, *B;
			
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
		
		void rotacionDI(nodoAVL*& aux){
			nodoAVL  *B, *C;
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
		
		void rotacionID(nodoAVL*& aux){
			nodoAVL  *B, *C;
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

		void balancear(nodoAVL*&aux){
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

		void insertar(int elem, nodoAVL*& aux){
			if(aux==NULL){
				this->cantElem++;
				aux=new nodoAVL();
				aux->dato=elem;
				return;
			}else if(elem < aux->dato){
				insertar(elem, aux->izq);
				
			}else{
				insertar(elem, aux->der);			
			}
			balancear(aux);
		}
		
		bool buscar(int elem, nodoAVL*& aux){
			if(aux==NULL)
				return false;
			if(aux->dato==elem)
				return true;
			if(elem<aux->dato)
				return buscar(elem, aux->izq);
			return buscar(elem, aux->der);		
		}

		
		void eliminar(int elem, nodoAVL*& aux){
			if(aux==NULL)
				return;
			if(elem==aux->dato){
				if(aux->izq==NULL and aux->der==NULL){
					this->cantElem--;
					delete aux;
					aux=NULL;
				}else if(aux->izq==NULL or aux->der==NULL){
					this->cantElem--;
					nodoAVL* aux2=aux;
					aux=(aux->izq==NULL?aux->der:aux->izq);
					delete aux2;
				}else{
					nodoAVL* aux2=aux->der;
					while(aux2->izq!=NULL)
						aux2=aux2->izq;
					int t=aux2->dato;
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
		
		nodoAVL * raiz;
		int cantElem;
	
		AVL(){
			raiz=NULL;
			cantElem=0;
		}
		
		void insertar(int elem){
			insertar(elem, raiz);
		}
		
		bool buscar(int elem){
			buscar(elem, raiz);
		}
		
		int tam(){
			return cantElem;
		}
		
		bool vacio(){
			return cantElem==0;
		}
		
		void eliminar(int elem){
			eliminar(elem, raiz);
		}
			
		void mostrar(nodoAVL* aux, int n){
			if(aux==NULL)
				return;
			for(int i=0;i<n;i++)
				printf("#");
			printf("%d", aux->dato);
			if(aux->izq!=NULL)
				printf(" Izquierda %d.", aux->izq->dato);
			if(aux->der!=NULL)
				printf(" Derecha %d. ", aux->der->dato);
			printf("\n");
			mostrar(aux->izq, n+1);
			mostrar(aux->der, n+1);
		}
			
		void mostrar(){
			mostrar(raiz, 0);
		}
};

int main(){
	AVL T;
	T.insertar(2);
	T.insertar(4);
	T.insertar(5);
	T.insertar(6);
	T.insertar(7);
	T.insertar(8);
	T.mostrar();
	return 0;
}

