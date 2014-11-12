#ifndef STRING2_H
#define STRING2_H

#include<iostream>
using namespace std;

class nodoString{
	public:
	char letra;
	nodoString *sig;
	nodoString(char l='\0'){
		letra=l;
		sig=NULL;
	}
};

class String{
	private:
		nodoString  inicio;
		nodoString * iterador;
		int len;
		int i;
	public:
		String(){
			//cout<<"constructor por defecto"<<endl;
			inicio.sig=NULL;
			iterador=NULL;
			i=-1;
			len=0;
		}
		char &operator[](int j){
			if(i>=j or iterador==NULL){
				i=0;
				iterador=inicio.sig;
			}
			for(;i<j;i++)
				iterador=iterador->sig;
			return iterador->letra;
		}
		char * toCharArray()const{
			char *p=new char[len];
			nodoString*aux=inicio.sig;
			for(int j=0;j<len;j++){
				*(p+j)=aux->letra;
				aux=aux->sig;
			}
			*(p+len)='\0';
			return p;
		}
		String(const String& otro){
			//cout<<"Constructor por copia"<<endl;
			iterador=&inicio;
			nodoString *iterador2=otro.inicio.sig;
			for(i=0;i<otro.len;i++){
				iterador->sig = new nodoString(iterador2->letra);
				iterador2=iterador2->sig;
				iterador=iterador->sig;
			}
			len=i;
			iterador->sig=NULL;
		}
		String(char a){
			//cout<<"Construcctor por char"<<endl;
			inicio.sig=new nodoString(a);
			len=1;
			iterador=NULL;
			i=-1;
		}
		String(char *a){
			//cout<<"Constructor por char*"<<endl;
			iterador=&inicio;
			for(i=0;*(a+i)!='\0';i++){
				iterador->sig=new nodoString(*(a+i));
				iterador=iterador->sig;
			}
			len=i;
			
		}
		void print(){
			for(int j=0;j<len;j++)
				cout<<operator[](j);
			cout<<endl;
		}
		int size(){
			return len;
		}
		String operator=(String otro){
			//cout<<"operador asignacion"<<endl;
			while(inicio.sig!=NULL){
				nodoString * aux=inicio.sig->sig;
				delete inicio.sig;
				inicio.sig=aux;
			}
			iterador=&inicio;
			for(i=0;i<otro.len;i++){
				iterador->sig=new nodoString(otro[i]);
				iterador=iterador->sig;
			}
			len=otro.len;
			return otro;
		}
		~String(){
			//cout<<"Adios mundo cruel"<<endl;
			while(inicio.sig!=NULL){
				nodoString * aux=inicio.sig->sig;
				delete inicio.sig;
				inicio.sig=aux;
			}
		}
		String operator+(char x){
			String otro=*(this);
			//cout<<x<<endl;
			nodoString *aux=&otro.inicio;
			while(aux->sig!=NULL)
				aux=aux->sig;
			aux->sig=new nodoString(x);
			otro.len++;
			return otro;
		}
		String operator+=(char x){
			*(this)=this->operator+(x);
			return *(this);
		}
		String operator+(String otro){
			String aux=*(this);
			for(int j=0;j<otro.len;j++)
				aux+=otro[j];
			return aux;
		}
		String operator+=(String otro){
			String aux=*(this);
			for(int j=0;j<otro.len;j++)
				aux+=otro[j];
			*(this)=aux;
			return aux;
		}
		String substring(int ini, int fin){
			String otro;
			for(int j=ini;j<=fin;j++)
				otro+=this->operator[](j);
			return otro;
		}
		bool operator<(String otro){
			int j=0;
			while(j<otro.len and j<len and this->operator[](j)==otro[j] ){
				j++;
			}
			if(otro.len==len)
				return false;
			if(otro.len>len)
				return true;
			if(len > otro.len)
				return false;
			return this->operator[](j)<otro[j];
		}
		bool operator>(String otro){
			return otro<*(this);
		}
		bool operator==(String otro){
			return not( otro<*(this) )and not (*(this)<otro); 
		}
		bool operator<=(String otro){
			return not (*(this)>otro);
		}
		bool operator>=(String otro){
			return not(*(this)<otro);
		}
		String(unsigned long long int x){
			String otro;
			while(x){
				otro=String('0'+x%10)+otro;
				x/=10;
			}
			*this=otro;
		}
		String(int x){
			String otro;
			if(x<0){
				otro='-';
				x=-x;
			}
			while(x){
				otro=String(char('0'+x%10))+otro;
				x/=10;
			}
			*this=otro;	
		}	
		String(long long int x){
			String otro;
			if(x<0){
				otro='-';
				x=-x;
			}
			while(x){
				otro=String(char('0'+x%10))+otro;
				x/=10;
			}
			*this=otro;	
		}
};

ostream &operator<<(ostream &stream,const String s){
	char *p=s.toCharArray();
	stream<<p;
	delete p;
	return stream;
}
istream &operator>>(istream &stream,String &n){
	String s;
	char x;
	while((x=cin.get())!='\n' and x!=' ')
		s+=x;
	n=s;
	return stream;
}

String readline(){
	String s;
	char x;
	while((x=cin.get())!='\n')
		s+=x;
	return s;
}

#endif
