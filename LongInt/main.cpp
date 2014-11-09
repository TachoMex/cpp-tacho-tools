#include <vector>
#include <iostream>
using namespace std;

class longInt{
	private:
		std::vector<bool> digitos;
		bool negativo;
	public:
		longInt():digitos(){
			negativo=false;
		}

		longInt(unsigned long long int n){
			digitos=std::vector<bool>();
			negativo=false;
			while(n){
				digitos.push_back(n&1);
				n>>=1;
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
			for(int i=0;i<digitos.size();i++)
				cout<<digitos[digitos.size()-i-1];
			cout<<endl;
		}
		longInt operator+(const longInt& b)const{
			longInt ans;
			bool acarreo=false;
			int i;
			for(i=0;i<max(digitos.size(),b.digitos.size());i++){
				ans.digitos.push_back((digitos.size()>i?digitos[i]:0)^(b.digitos.size()>i?b.digitos[i]:0)^acarreo);
				acarreo = (digitos.size()>i?digitos[i]:0)&(b.digitos.size()>i?b.digitos[i]:0) or (digitos.size()>i?digitos[i]:0)&acarreo or acarreo&(b.digitos.size()>i?b.digitos[i]:0); 
			}
			if(acarreo)
				ans.digitos.push_back(1);
			return ans;

		}

		longInt complemento2(int tam)const{
			longInt ans;
			ans.digitos = std::vector<bool>(tam);
			for(int i=0;i<digitos.size();i++)
				ans.digitos[i] = digitos[i];
			ans.digitos.flip();
			return longInt(1)+ans;

		}

		longInt operator+=(const longInt& b){
			longInt ans = operator+(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}

		longInt operator-(const longInt& b)const{
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
			ans.digitos=std::vector<bool>(a);
			ans.digitos.insert(ans.digitos.end(),digitos.begin(), digitos.end());
			return ans;
		}

		longInt operator*(const longInt& c){
			if(digitos.size()<=1){
				return (digitos.size()==0 or not digitos[0]?0:c);
			}if(c.digitos.size()<=1){
				return (c.digitos.size()==0 or not c.digitos[0]?0:*this);
			}

			longInt b=c;
			while(digitos.size()<b.digitos.size())
				digitos.push_back(0);
			while(b.digitos.size()<digitos.size())
				b.digitos.push_back(0);

			longInt x0,x1,y0,y1,z0,z1,z2;
			int n=digitos.size()/2;
			x0.digitos = vector<bool>(digitos.begin(),digitos.begin()+n);
			x1.digitos = vector<bool>(digitos.begin()+n,digitos.end());
			int m=b.digitos.size()/2;
			y0.digitos = vector<bool>(b.digitos.begin(),b.digitos.begin()+m);
			y1.digitos = vector<bool>(b.digitos.begin()+m,b.digitos.end());
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
					if(digitos[i] and !b.digitos[i])
						return false;
					else if(b.digitos[i] and !digitos[i])
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

		longInt operator>>(int n)const{
			longInt ans;
			ans.digitos = std::vector<bool>(digitos.begin()+n,digitos.end());
			return ans;
		}

		longInt operator>>=(int n){
			longInt ans = operator>>(n);
			digitos=ans.digitos;
			return ans;
		}



		longInt operator/(const longInt& b)const{
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
				if(b<<med >= a){
					corrimiento = med;
					fin = med-1;
				}else{
					ini = med + 1;
				}
			}
			aux=b<<corrimiento;
			for(;corrimiento>=0;corrimiento--){
				if(a>=aux){
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


		longInt operator%(const longInt& b)const{
			return operator-(operator/(b)*b);
		}


		longInt operator%=(const longInt& b){
			longInt ans = operator%(b);
			negativo = ans.negativo;
			digitos = ans.digitos;
			return ans;
		}
		
		friend longInt pow(const longInt& a,const longInt& b,const longInt& c);
		friend longInt pow(const longInt& a,const longInt& b);

};

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


int cont=0;
longInt pow(const longInt& a,const longInt& b){
	b.mostrar();
	if(b==0)
		return 1;
	if(b==1)
		return a;
	longInt t=pow(a,b>>1);
	b.mostrar();
	return (b.digitos[0]?t*t*a:t*t);
} 

longInt pow(const longInt& a, unsigned long long int b){
	cout<<b<<":::";
	a.mostrar();
	if(b==0)
		return 1;
	if(b==1)
		return a;
	cout<<"IN"<<endl;
	longInt t=pow(a,b/2);
	cout<<"OUT"<<endl;
	t.mostrar();
	return (b%2?t*t*a:t*t);
}

bool testPrimalidadFermat(longInt p){
	return p==2 or pow(2,p,p)==2;
}

int main(){
	longInt y = pow(123133123,12322);
//	longInt z = pow(111111111,1000);
	y.mostrar();
//	z.mostrar();
	

	return 0;
}