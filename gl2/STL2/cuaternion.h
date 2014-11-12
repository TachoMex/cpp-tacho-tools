#ifndef CUATERNION_H
#define CUATERNION_H
#include<string>

#include <cmath>

struct cuaternion{
		double r,i,j,k;
};

		cuaternion Cuaternion(){
			cuaternion q;
			q.i=q.j=q.k=q.r=0;
			return q;
		}

		cuaternion Cuaternion(double a,double b,double c,double d){
			cuaternion q;
			q.r=a;
			q.i=b;
			q.j=c;
			q.k=d;
			return q;
		}

		cuaternion Cuaternion(double a){
			cuaternion q;
			q.r=a;
			q.i=q.j=q.k=0;
			return q;
		}

		double norma2(cuaternion q){
			return q.r*q.r+q.i*q.i+q.j*q.j+q.k*q.k;
		}
		double norma(cuaternion q){
			return sqrt(q.r*q.r+q.i*q.i+q.j*q.j+q.k*q.k);
		}

		cuaternion operator*(cuaternion q, double f){
			return Cuaternion(f*q.r, f*q.i, f*q.j, f*q.k);
		}

		cuaternion operator+(cuaternion q, cuaternion c){
			return Cuaternion(q.r+c.r, q.i+c.i, q.j+c.j, q.k+c.k);
		}

		cuaternion operator-(cuaternion q, cuaternion c){
			return Cuaternion(q.r-c.r, q.i-c.i, q.j-c.j, q.k-c.k);
		}

		cuaternion operator*(cuaternion q, cuaternion b){
			return Cuaternion(
				q.r*b.r - q.i*b.i - q.j*b.j - q.k*b.k,
				q.r*b.i + q.i*b.r + q.j*b.k - q.k*b.j,
				q.r*b.j - q.i*b.k + q.j*b.r + q.k*b.i,
				q.r*b.k + q.i*b.j - q.j*b.i + q.k*b.r
			);
		}

		cuaternion conjugado(cuaternion q){
			return Cuaternion(q.r,-q.i,-q.j,-q.k);
		}

		cuaternion operator/(cuaternion q, cuaternion b){
			return q * conjugado(b) * (1.0/norma2(b));
		}
		std::string toString(cuaternion q){
			return std::to_string(q.r) + " , " + std::to_string(q.i) + " , " + std::to_string(q.j) + " , " + std::to_string(q.k);
		}

		#ifdef PUNTO4D_H
		_4D::punto convertir(cuaternion q){
			return _4D::punto(q.r,q.i,q.j,q.k);
		}
		#endif
#endif