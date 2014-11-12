#include<iostream>
#include"string2.h"
using namespace std;

class Long{
	private:
		bool signo;
		String valor;
	public:
		Long (){
			signo=false;
			valor=0;
		}
		Long(int x){
			signo=false;
			if(x<0){
				signo=true;
				x=-x;
			}
			valor=String(x);
		}
		Long(Long x){
			signo=x.signo;
			valor=x.valor;
		}
		Long(long long int x){
			signo=false;
			if(x<0){
				signo=true;
				x=-x;
			}
			valor=String(x)
		}
		Long(unsigned long long int x){
			signo=false;
			valor=String(x);
		}
		Long exp10(unsigned int n){
			
		}
		bool operator<(Long x);
		bool operator>(Long x);
		bool operator<=(Long x);
		bool operator>=(Long x);
		bool operator==(Long x);
		bool operator!=(Long x);
		Long operator+(Long x);
		Long operator-(Long x);
		Long operator*(Long x);
		Long operator/(Long x);
		Long operator^(Long x);
		Long operator%(Long x);
		Long operator++();
		Long operator--();
		Long operator=();
		friend ostream &operator<<(ostream&, const Long);
};

