#ifndef RECTANGULO2D_H
#define RECTANGULO2D_H
#include"../macros.h"
#include"linea.h"
	namespace _2D{
	class rectangulo : public linea {
		public:
			rectangulo():linea(){}
			rectangulo(punto a, punto b):linea(a, b){}
			rectangulo(punto a, double b, double c): linea(a,a+punto(b,c)){}
			double base()const{
				return fin.x-inicio.x;
			}
			double altura()const{
				return fin.y-inicio.y;
			}
			double area()const{
				return base()*altura();
			}
			punto centro()const{
				return punto((inicio.x+fin.x)/2,(inicio.y+fin.y)/2);
			}
			rectangulo interseccion(rectangulo o)const{
				punto a(MAYOR(inicio.x, o.inicio.x), MAYOR(inicio.y, o.inicio.y));
				punto b(MENOR(fin.x, o.fin.x), MENOR(fin.y, o.fin.y));
				if(a.x > b.x or a.y > b.y)
					return rectangulo(punto(0,0),0,0);
				else 
					return rectangulo(a, b);
			}
	};
}
#endif