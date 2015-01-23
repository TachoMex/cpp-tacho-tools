#ifndef LINEA2D_H
#define LINEA2D_H

#include "punto.h"
#include <cmath>

namespace _2D{
	template<class T>
	class linea{
		public:
			punto<T> inicio;
			punto<T> fin;
			linea<T>();
			linea<T>(const punto<T>& a,const punto<T>& b);
			linea<T>(const punto<T>& ini, T r, T a);
			T angulo() const;
			linea<T> rotar(T ang)const ;		
			T longitud() const;
			linea operator*(T d) const;
			linea operator*=(T d);
			std::string toString()const{
				return inicio.toString()+std::string("->")+fin.toString();
			}
	};

	template<class T>
	punto<T> interseccion(const linea<T>& a,const linea<T>& b);
	
	template<class T>
	linea<T>::linea():inicio(),fin(){
	}

	template<class T>
	linea<T>::linea(const punto<T>& a,const punto<T>& b){
		inicio=a;
		fin=b;
	}
	
	template<class T>
	linea<T>::linea(const punto<T>& ini, T r, T a){
		inicio=ini;
		fin=punto<T>(ini.x+r*cos(a), ini.y+r*sin(a));
	}

	template<class T>
	T linea<T>::angulo()const {
		return (fin - inicio).angulo();
	}

	template<class T>
	linea<T> linea<T>::rotar(T ang)const {
		return linea(inicio, longitud(), angulo()+ang); 
	}


	template<class T>
	T linea<T>::longitud()const{
		return (fin-inicio).norma();
	}

	template<class T>
	linea<T> linea<T>::operator*(T d)const{
		return linea(inicio, longitud()*d, angulo());
	}
	template<class T>
	linea<T> linea<T>::operator*=(T d){
		*this=*this*d;
		return *this;
	}
}
#endif
