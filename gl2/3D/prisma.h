#include"linea.h"
namespace _3D{
	class prisma:public linea{
		public:
			prisma():linea(){}
			prisma(punto i, punto f):linea(i,f){}
			prisma(punto a, double b, double c, double d):linea(a,b,c,d){}
			prisma(linea l):linea(l){}
			
			punto centro()const{
				return inicio+(fin-inicio)*0.5;
			}
	};
}