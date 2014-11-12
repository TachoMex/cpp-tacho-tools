#ifndef PUNTO4D_H
#define PUNTO4D_H
#include "../macros.h"

namespace _4D{
	class punto{
		public:
			double x,y,z,w;
			punto(){
				z=x=y=w=0;
			}
			punto(double a, double b, double c, double d){
				x=a;
				y=b;
				z=c;
				w=d;
			}

			double norma()const{
				return sqrt(x*x+y*y+z*z+w*w);
			}
			double norma2()const{
				return x*x+y*y+z*z+w*w;
			}
			punto operator+(const punto& otro)const{
				return punto(x+otro.x, y+otro.y, z+otro.z,w+otro.w);
			}
			punto operator-(const punto& otro)const{
				return punto(x-otro.x, y-otro.y, z-otro.z,w-otro.w);
			}
			punto operator*(double f)const {
				return punto(x*f, y*f, z*f,w*f);
			}

			punto operator-=(const punto& otro){
				x-=otro.x;
				y-=otro.y;
				z-=otro.z;
				w-=otro.w;
				return *this;
			}

			punto operator+=(const punto& otro){
				x+=otro.x;
				y+=otro.y;
				z+=otro.z;
				w+=otro.w;
				return *this;
			}

			punto operator*=(double f){
				x*=f;
				y*=f;
				z*=f;
				w*=f;
				return *this;
			}

			punto unitario()const{
				double u=norma();
				return punto(x/u, y/u, z/u,w/u);
			}
			std::string toString()const{
				return std::string("(")+std::to_string(x)+std::string(" , ")+std::to_string(y)+std::string(" , ")+std::to_string(z)+std::string(",")+std::to_string(w)+std::string(")");
			}

	};

	double productoPunto(const punto& a, const punto& b){
		return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
	}

	punto productoCruz(const punto& a, const punto& b, const punto& c){
		return punto(
			a.y*(b.z*c.w - c.z*b.w) - a.z*(b.y*c.w - c.y*b.w) + a.w*(b.y*c.z - c.y*b.z),
			-a.x*(b.z*c.w - c.z*b.w) + a.z*(b.x*c.w - c.x*b.w) - a.w*(b.x*c.z - c.x*b.z), 
			a.x*(b.y*c.w - c.y*b.w) - a.y*(b.x*c.w - c.x*b.w) + a.w*(b.x*c.y - c.x*b.y) ,
			-a.x*(b.y*c.z - c.y*b.z) + a.y*(b.x*c.z - c.x*b.z) - a.z*(b.x*c.y - c.x*b.y)
		);
	}

	punto puntoDeVista(const punto& desde, const punto& hacia, const punto& arriba, const punto& sobre, const punto&  p){
		punto A, B, C, D;

		D = (hacia-desde).unitario();
		A = productoCruz(arriba, sobre, D).unitario();
		B = productoCruz(sobre, D, A).unitario();
		C = productoCruz(D, A, B);

		punto temp = p-desde;

		return punto(productoPunto(temp,A), productoPunto(temp,B), productoPunto(temp,C), productoPunto(temp,D));
 
	}
}

#endif