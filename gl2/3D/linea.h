#ifndef LINEA3D_H
#define LINEA3D_H

#include"punto.h"

namespace _3D{
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
	
			linea(const punto& i, double hx, double hy, double hz){
				inicio=i;
				fin=i+punto(hx, hy, hz);
			}
			
			double longitud()const{
				return (fin-inicio).norma();
			}
			
			std::string toString()const{
				return inicio.toString()+std::string("->")+fin.toString();
			}
			
			linea operator*(double k)const{
				return linea(inicio,inicio+(fin-inicio)*k); 
			}
	};
}

#endif