#include <vector>
#include <iostream>
using namespace std;

class longInt{
	private:
		std::vector<unsigned char> digitos;
		bool negativo;
	public:
		longInt():digitos(){
			negativo=false;
		}

		longInt(unsigned long long int n){
			digitos=std::vector<unsigned char>();
			negativo=false;
			while(n){
				digitos.push_back(n&0xff);
				n>>=8;
			}
		}

		longInt(const longInt& b){
			digitos = b.digitos;
			negativo = b.negativo;
		}

		longInt operator=(const longInt& b){
			digitos = b.digitos;
			negativo = b.negativo;
			return b;
		}

		void mostrar() const{
			cout<<"0x";
			for(int i=0;i<digitos.size();i++){
				unsigned char d = digitos[digitos.size()-i-1];
				unsigned char a = d&0x0f;
				unsigned char b = (d&0xf0)>>4;
				a = (a<=9?'0'+a:'A'+a-10);
				b = (b<=9?'0'+b:'A'+b-10);
				cout<<b<<a;
			}
			cout<<endl;
		}

		longInt operator+(const longInt& b)const{
			longInt ans;
			int acarreo=0;
			int i;
			for(i=0;i<max(digitos.size(),b.digitos.size());i++){
				
				int nuevoDigito = acarreo + (i>=b.digitos.size()?0:b.digitos[i]) + (i>=digitos.size()?0:digitos[i]);
				acarreo = nuevoDigito>>8;
				nuevoDigito&=0xff;

				ans.digitos.push_back(nuevoDigito);
			}
			if(acarreo)
				ans.digitos.push_back(acarreo);
			return ans;

		}

		longInt complemento2(int tam=-1)const{
			if(tam==-1)
				tam = digitos.size();
			longInt ans;
			ans.digitos = std::vector<unsigned char>(tam);
			for(int i=0;i<digitos.size();i++)
				ans.digitos[i] = 0xff-digitos[i];
			return longInt(1)+ans;

		}

		
		longInt operator+=(const longInt& b){
			longInt ans = operator+(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}

		longInt operator-(const longInt& b){
			longInt ans = operator+(b.complemento2(digitos.size()+1));
			ans.digitos.pop_back();
			while(!ans.digitos.empty() and ans.digitos.back()==0)
				ans.digitos.pop_back();
			return ans;

		}

		longInt operator-=(const longInt& b){
			longInt ans = operator-(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}
		
		longInt operator<<(int a)const{
			longInt ans;
			ans.digitos=std::vector<unsigned char>(a);
			ans.digitos.insert(ans.digitos.end(),digitos.begin(), digitos.end());
			return ans;
		}

	private:
		longInt mul(unsigned char b)const{
			longInt ans;
			int acarreo=0;
			int i;
			for(i=0;i<digitos.size();i++){
				int nuevoDigito = acarreo +  int(b)*digitos[i];
				acarreo = nuevoDigito>>8;
				nuevoDigito&=0xff;
				ans.digitos.push_back(nuevoDigito);
			}
			if(acarreo)
				ans.digitos.push_back(acarreo);
			return ans;
		}
	public:

		longInt operator*(const longInt& c){
			if(digitos.size()<=1){
				return (digitos.size()==0?0:c.mul(digitos[0]));
			}if(c.digitos.size()<=1){
				return (c.digitos.size()==0?0:mul(c.digitos[0]));
			}
			longInt b=c;
			longInt x0,x1,y0,y1,z0,z1,z2;
			int n=digitos.size()/2;
			x0.digitos = vector<unsigned char>(digitos.begin(),digitos.begin()+n);
			x1.digitos = vector<unsigned char>(digitos.begin()+n,digitos.end());
			int m=b.digitos.size()/2;
			y0.digitos = vector<unsigned char>(b.digitos.begin(),b.digitos.begin()+m);
			y1.digitos = vector<unsigned char>(b.digitos.begin()+m,b.digitos.end());
			z2=x1*y1;
			z0=x0*y0;
			z1=(x1+x0)*(y1+y0)-z2-z0;
			return (z2<<(n+n))+(z1<<n)+z0;
		}
		longInt operator*=(const longInt& b){
			longInt ans = operator*(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}


		bool operator<(const longInt& b)const{
			if(digitos.size()<b.digitos.size()){
				return true;
			}
			else if(digitos.size()>b.digitos.size()){
				return false;
			}else{
				for(int i=b.digitos.size()-1;i>=0;i--)
					if(digitos[i] > b.digitos[i])
						return false;
					else if(b.digitos[i] > digitos[i])
						return true;
			}
			return false;
		}


		bool operator>(const longInt& b)const {
			return b<*this;
		}

		bool operator==(const longInt& b)const{
			if(b.digitos.size()!=digitos.size())
				return false;
			return b.digitos == digitos;
		}

		bool operator!=(const longInt& b)const{
			return !(operator==(b));
		}

		bool operator<=(const longInt& b)const{
			return !operator>(b);
		}

		bool operator>=(const longInt& b)const{
			return !operator<(b);
		}

		
		longInt operator>>(int n){
			longInt ans;
			ans.digitos = std::vector<unsigned char>(digitos.begin()+n,digitos.end());
			return ans;
		}

		longInt operator>>=(int n){
			longInt ans = operator>>(n);
			digitos=ans.digitos;
			return ans;
		}

		/*

		longInt operator/(const longInt& b){
			if(operator<(b))
				return 0;
			longInt ans;
			longInt aux=b;
			longInt a;
			a.digitos = digitos;
			int corrimiento=0;
			int ini=0;
			int fin=1<<digitos.size()+1;
			while(ini<=fin){
				int med=(ini+fin)/2;
				if(b<<med > a){
					corrimiento = med;
					fin = med-1;
				}else{
					ini = med + 1;
				}
			}
			aux=b<<corrimiento;
			for(;corrimiento>=0;corrimiento--){
				if(a>aux){
					ans+=longInt(1)<<corrimiento;
					a-=b<<corrimiento;
				}
				aux>>=1;
			}
			return ans;
		}


		longInt operator/=(const longInt& b){
			longInt ans = operator/(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}


		longInt operator%(const longInt& b){
			return operator-(operator/(b)*b);
		}


		longInt operator%=(const longInt& b){
			longInt ans = operator%(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}
		
		*/
		//friend longInt pow(const longInt& a,const longInt& b,const longInt& c);
		friend longInt pow(const longInt& a,long long int b);
};
/*
longInt pow(const longInt& a,const longInt& b,const longInt& c){
	longInt ans=1;
	longInt pot = a;
	for(int i=0;i<b.digitos.size();i++){
		cout<<i<<"/"<<b.digitos.size()<<endl;
		if(b.digitos[i]){
			ans*=pot;
			if(ans>c)
				ans%=c;
		}
		pot*=pot;
		if(pot>c)
		pot%=c;
	}
	return ans;
} 

*/
longInt pow(const longInt& a,long long int b){
	if(b==0)
		return 1;
	if(b==1)
		return a;
	longInt t = pow(a,b/2);
	t = t*t*pow(a,b%2);
	return t;
} 





int main(){
	longInt a(10002);
	pow(a,1007).mostrar();
	return 0;
}