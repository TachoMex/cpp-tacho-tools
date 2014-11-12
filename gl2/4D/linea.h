#ifndef LINEA4D_H
#define LINEA4D_H

#include"punto.h"

namespace _4D{
	class linea{
		public:
			punto inicio, fin;
			
			linea():inicio(),fin(){}
			
			linea(punto i, punto f){
				inicio=i;
				fin=f;
			}
			
			linea(const linea& l){
				inicio=l.inicio;
				fin=l.fin;
			}
	
			linea(punto i, double hx, double hy, double hz, double hw){
				inicio=i;
				fin=i+punto(hx, hy, hz,hw);
			}
			
			double longitud(){
				return (fin-inicio).norma();
			}
			
			std::string toString(){
				return inicio.toString()+std::string("->")+fin.toString();
			}
			
			linea operator*(double k){
				return linea(inicio,inicio+(fin-inicio)*k); 
			}
	};
}

#endif