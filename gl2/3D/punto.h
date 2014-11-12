#ifndef PUNTO3D_H
#define PUNTO3D_H

#include <cmath>
#include <string>
#include "../macros.h"
#include "angulo.h"

namespace _3D{
	class punto{
		public:
			double x, y, z;
			punto(){
				x=y=z=0;
			}
			punto(double X, double Y,double Z){
				x=X;
				y=Y;
				z=Z;
			}
			double norma() const{
				return sqrt(x*x+y*y+z*z);
			}
			double norma2() const{
				return x*x+y*y+z*z;
			}
			punto operator+(const punto& otro) const{
				return punto(x+otro.x, y+otro.y, z+otro.z);
			}
			punto operator-(const punto& otro) const{
				return punto(x-otro.x, y-otro.y, z-otro.z);
			}
			punto operator-=(const punto& otro){
				x-=otro.x;
				y-=otro.y;
				z-=otro.z;
				return *this;
			}
			punto operator*(double f)const {
				return punto(x*f, y*f, z*f);
			}
			punto unitario() const {
				double u=norma();
				return punto(x/u, y/u, z/u);
			}
			std::string toString()const {
				return std::string("(")+std::to_string(x)+std::string(" , ")+std::to_string(y)+std::string(" , ")+std::to_string(z)+std::string(")");
			}
	};

	double productoPunto(const punto& a,const punto& b){
		return a.x*b.x + a.y*b.y + a.z*b.z; 
	}

	punto productoCruz(const punto& a,const punto& b){
		return punto(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
	}

	punto puntoDeVista(const punto& desde,const punto& hacia,const punto& arriba,const punto& p){
		punto A, B, C;
		C=(hacia-desde).unitario();
		A=productoCruz(arriba, C).unitario();
		B=productoCruz(C,A);
		punto aux=p-desde;
		return punto(productoPunto(aux, A), productoPunto(aux,B), productoPunto(aux,C));
	}

}

#endif