#ifndef LINEA2D_H
#define LINEA2D_H

#include "punto.h"
#include <cmath>

namespace _2D{
	class linea{
		public:
			punto inicio;
			punto fin;
			linea();
			linea(const punto& a,const punto& b);
			linea(const punto& ini, double r, double a);
			double angulo() const;
			linea rotar(double ang)const ;		
			double longitud() const;
			linea operator*(double d) const;
			linea operator*=(double d);
			std::string toString()const {
				return inicio.toString()+std::string("->")+fin.toString();
			}
	};

	punto interseccion(const linea& a,const linea& b);
	linea::linea(){
		inicio=fin=punto(0,0);
	}
	linea::linea(const punto& a,const punto& b){
		inicio=a;
		fin=b;
	}
	linea::linea(const punto& ini, double r, double a){
		inicio=ini;
		fin=punto(ini.x+r*cos(a), ini.y+r*sin(a));
	}

	double linea::angulo()const {
		return (fin - inicio).angulo();
	}

	linea linea::rotar(double ang)const {
		return linea(inicio, longitud(), angulo()+ang); 
	}

	double linea::longitud()const{
		return (fin-inicio).norma();
	}
	linea linea::operator*(double d)const{
		return linea(inicio, longitud()*d, angulo());
	}
	linea linea::operator*=(double d){
		*this=*this*d;
		return *this;
	}
}
#endif
