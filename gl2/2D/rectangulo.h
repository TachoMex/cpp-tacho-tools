#ifndef RECTANGULO2D_H
#define RECTANGULO2D_H
#include"../macros.h"
#include"linea.h"
	namespace _2D{

	template<class T>
	class rectangulo : public linea<T> {
		public:
			rectangulo():linea<T>(){}
			rectangulo(punto<T> a, punto<T> b):linea<T>(a, b){}
			rectangulo(punto<T> a, T b, T c): linea<T>(a,a+punto<T>(b,c)){}
			T base() const{
				return this->fin.x-this->inicio.x;
			}
			T altura() const{
				return this->fin.y-this->inicio.y;
			}
			T area() const{
				return base()*altura();
			}
			punto<T> centro()const{
				return punto<T>((this->inicio.x+this->fin.x)/2,(this->inicio.y+this->fin.y)/2);
			}
			rectangulo<T> interseccion(rectangulo<T> o)const{
				punto<T> a(MAYOR(this->inicio.x, o.inicio.x), MAYOR(this->inicio.y, o.inicio.y));
				punto<T> b(MENOR(this->fin.x, o.fin.x), MENOR(this->fin.y, o.fin.y));
				if(a.x > b.x or a.y > b.y)
					return rectangulo<T>();
				else 
					return rectangulo<T>(a, b);
			}
	};
}
#endif