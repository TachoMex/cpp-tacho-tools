#ifndef PUNTO2D_H
#define PUNTO2D_H

#include <string>
#include <cstdlib>
#include <cmath>

namespace _2D{

	template<class T>
	class punto{
		public:
			T x,y;
			punto(T,T);
			punto();
			std::string toString() const;
			punto<T> operator+(const punto<T>& b) const{
				return punto<T>(x+b.x, y+b.y);
			}
			punto<T> operator+=(const punto<T>& b){
				*this=*this+b;
				return *this;
			}
			punto<T> operator-(const punto<T>& b)const {
				return punto<T>(x-b.x, y-b.y);
			}
			punto<T> operator-=(const punto<T>& b){
				*this=*this-b;
				return *this;
			}
			punto<T> operator*(T r)const {
				return punto<T>(x*r, y*r);
			}
			punto<T> operator/(T r)const{
				return punto<T>(x/r, y/r);
			}
			static punto<double> polar(double r , double ang){
				return punto(r*cos(ang), r*sin(ang));
			}
			T angulo() const{
				return atan2(y, x);
			}
			T norma() const;
			T norma2() const{
				return x*x+y*y;
			}
	};

	template<class T>
	punto<T>::punto(T x ,T y){
		this->x=x;
		this->y=y;
	}

	template<class T>
	punto<T>::punto():x(), y(){
	}

	template<class T>
	std::string punto<T>::toString() const{
		std::string ret="";
		ret+='(';
		ret+=std::to_string(this->x);
		ret+=',';
		ret+=std::to_string(this->y);
		ret+=')';
		return ret;
	}

	template<class T>
	T distancia(const punto<T>& a,const punto<T>& b){
		T dx= std::abs(a.x-b.x);
		T dy= std::abs(a.y-b.y);
		return sqrt( dx*dx - dy*dy);
	}

	template<class T>
	T punto<T>::norma()const{
		return sqrt(x*x+y*y);
	}

	template<class T>
	T productoPunto(const punto<T>& a,const punto<T>& b){
		return a.x*b.x+a.y*b.y;
	}

	template<class T>
	T productoCruz(const punto<T>& a,const punto<T>& b){
		return a.x*b.y-a.y*b.x;
	}
}
#endif