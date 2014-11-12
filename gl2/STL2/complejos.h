#ifndef COMPLEJOS_H
#define COMPLEJOS_H
#include<iostream>
#include<cmath>
using namespace std;
class complejo{
	public:
	static double PRECISION;
	double a,b;
	complejo(double x,double y);
	complejo();
	complejo(const complejo& otro);
	complejo inv();
	complejo operator+(complejo otro);
	complejo operator*(complejo otro);
	complejo operator-(complejo otro);
	double angulo();
	complejo operator/(complejo otro);
	complejo operator=(complejo otro);
	bool operator==(complejo otro);
	bool operator==(double otro);
	complejo operator+(double otro);
	complejo operator-(double otro);
	complejo operator*(double otro);
	complejo operator/(double otro);
	complejo operator^(double n);
	complejo operator^(int n);
};
double complejo::PRECISION=0.00;
complejo sin(complejo x){
	return complejo(sin(x.a)*cosh(x.b),cos(x.a)*sinh(x.b));
}
complejo cos(complejo x){
	return complejo(cos(x.a)*cosh(x.b), sin(x.a)*sinh(x.b));
}
complejo tan(complejo x){
	return complejo((sin(2*x.a))/(cos(2*x.a)+cosh(2*x.b)),(sinh(2*x.b))/(cos(2*x.a)+cosh(2*x.b)));
}
complejo exp(complejo x){
	return complejo(exp(x.a)*cos(x.b), exp(x.a)*sin(x.b));
}
complejo ln(complejo x){
	return complejo(0.5*log(x.a*x.a+x.b*x.b),atan(x.b/x.a));
}
double abs(complejo x){
	return sqrt(x.a*x.a+x.b+x.b);
}
complejo operator+(double a, complejo b){
	return b+a;
}
complejo operator-(double a, complejo b){
	return b-a;
}
complejo operator*(double a, complejo b){
	return b*a;
}
complejo operator/(double a, complejo b){
	return b/a;
}
ostream &operator<<(ostream &stream,const complejo n){
	if(n.b==0){
		stream <<n.a;
	}else if(n.a==0){
		stream<<n.b<<"i";
	}else if(n.b>0){
		stream<<n.a<<"+"<<n.b<<"i";
	}else{
		stream<<n.a<<n.b<<"i";
	}
	return stream;
}
istream &operator>>(istream &stream,complejo n){
	stream>>n.a>>n.b;
	return stream;
}
complejo complejo_i(0,1);


complejo::complejo(double x,double y){
	a=x;
	b=y;
}
complejo::complejo(){
	a=0;
	b=0;
}
complejo::complejo(const complejo& otro){
	a=otro.a;
	b=otro.b;
}
complejo complejo::inv(){
	return complejo(a/(a*a+b*b),-b/(a*a+b*b));
}
complejo complejo::operator+(complejo otro){
	return complejo(a+otro.a,b+otro.b);
}
complejo complejo::operator*(complejo otro){
	return complejo(a*otro.a-(b*otro.b),a*otro.b+b*otro.a);
}
complejo complejo::operator-(complejo otro){
	return complejo(a-otro.a,b-otro.b);
}
double complejo::angulo(){
	return atan2(b,a);
}
complejo complejo::operator/(complejo otro){
	return *(this)*otro.inv();
}
complejo complejo::operator=(complejo otro){
	a=otro.a;
	b=otro.b;
}
bool complejo::operator==(complejo otro){
	return abs(a-otro.a)<=this->PRECISION and abs(b-otro.b)<=this->PRECISION;
}
bool complejo::operator==(double otro){
	return abs(b)<=this->PRECISION and abs(a-otro)<=this->PRECISION;
}
complejo complejo::operator+(double otro){
	return *(this)+complejo(otro,0);
}
complejo complejo::operator-(double otro){
	return *(this)-complejo(otro,0);
}
complejo complejo::operator*(double otro){
	return *(this)*complejo(otro,0);
}
complejo complejo::operator/(double otro){
	return *(this)+complejo(otro,0);
}
complejo complejo::operator^(double n){
	return pow(angulo(),n)*(cos(angulo()*n)+complejo_i*sin(angulo()*n));
}
complejo complejo::operator^(int n){
	if(n<0)
		return (*(this)^(-n)).inv();
	if(n==0) return complejo(1,0);
	if(n==1) return complejo(a,b);
	complejo x=(*this)^(n/2);
	x=x*x;
	if(n%2) x=x**this;
	return x;
}
#endif