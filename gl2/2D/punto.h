#ifndef PUNTO2D_H
#define PUNTO2D_H

#include <string>
#include <cstdlib>
#include <cmath>

namespace _2D{
	class punto{
		public:
			double x,y;
			punto(double,double);
			punto();
			std::string toString() const;
			punto operator+(const punto& b) const{
				return punto(x+b.x, y+b.y);
			}
			punto operator+=(const punto& b){
				*this=*this+b;
				return *this;
			}
			punto operator-(const punto& b)const {
				return punto(x-b.x, y-b.y);
			}
			punto operator-=(const punto& b){
				*this=*this-b;
				return *this;
			}
			punto operator*(double r)const {
				return punto(x*r, y*r);
			}
			static punto polar(double r , double ang){
				return punto(r*cos(ang), r*sin(ang));
			}
			double angulo() const{
				return atan2(y, x);
			}
			double norma() const;
	};

	punto::punto(double x ,double y){
		this->x=x;
		this->y=y;
	}

	punto::punto(){
		this->x=this->y=0;
	}

	std::string punto::toString() const{
		std::string ret="";
		ret+='(';
		ret+=std::to_string(this->x);
		ret+=',';
		ret+=std::to_string(this->y);
		ret+=')';
		return ret;
	}

	double distancia(const punto& a,const punto& b){
		double dx= std::abs(a.x-b.x);
		double dy= std::abs(a.y-b.y);
		return sqrt( dx*dx - dy*dy);
	}

	double punto::norma()const{
		return sqrt(x*x+y*y);
	}

	double productoPunto(const punto& a,const punto& b){
		return a.x*b.x+a.y*b.y;
	}

	double productoCruz(const punto& a,const punto& b){
		return a.x*b.y-b.x*a.y;
	}
}
#endif