#include "color.h"

class YcbcrColor{
	public:
		float y;
		float cb;
		float cr;
	YcbcrColor(){
		y=0;
		cb=0;
		cr=0;
	}
	YcbcrColor(const Color& u){
		float r,g,b;
		r=u.r;
		g=u.g;
		b=u.b;
		y = 0.299*r+0.587*g+0.114*b;
		cb = -0.1687*r-0.3313*g+0.5*b+128;
		cr = 0.5*r-0.4187*g-0.0813*b+128;
	}
};

class Matrix8x8{
private:
	float *datos;
public:
	Matrix8x8(){
		datos = new float[64];
		memset(datos,0,sizeof(datos));
	}
	const float* operator[](int i) const{
		return datos+8*i;
	}

	float* operator[](int i){
		return datos+8*i;
	}

	Matrix8x8(const float matriz[8][8]){
		datos = new float[64];
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				datos[i*8+j]=matriz[i][j];
			}
		}
	}

	Matrix8x8 operator*(const Matrix8x8& b)const{
		Matrix8x8 c;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				c[i][j]=0.0;
				for(int k=0;k<8;k++){
					c[i][j]+=datos[i*8+k]*b[k][j];
				}
			}
		}
		return c;
	}


	Matrix8x8 traspuesta()const{
		Matrix8x8 res;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				res[i][j]=datos[i+j*8];
			}
		}
		return res;
	}

	~Matrix8x8(){
		delete[] datos;
	}

	Matrix8x8(const Matrix8x8& b){
		datos=new float[64];
		for(int i=0;i<64;i++){
			datos[i]=b.datos[i];
		}
	}

	Matrix8x8 operator=(const Matrix8x8& b){
		delete[] datos;
		datos=new float[64];
		for(int i=0;i<64;i++){
			datos[i]=b.datos[i];
		}
		return b;
	}

	const static Matrix8x8 Losheller; 
	const static Matrix8x8 DCTMatrix; 
	friend std::ostream& operator<<(std::ostream&,const Matrix8x8&);
};
const float LoshellerFloat[8][8] = {
	{16,11,10,16,24,40,51,61},
	{12,12,14,19,26,58,60,55},
	{14,13,16,24,40,57,69,56},
	{14,17,22,29,51,87,80,62},
	{18,22,37,56,68,109,103,77},
	{24,35,55,64,81,104,113,92},
	{49,64,78,87,103,121,120,101},
	{72,92,95,98,112,100,103,99}
};
const Matrix8x8 Matrix8x8::Losheller(LoshellerFloat);

std::ostream& operator<<(std::ostream& s, const Matrix8x8& m){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			s<<m[i][j]<<'\t';
		}
		s<<std::endl;
	}
	return s;
}


Matrix8x8 DCTM(){
	Matrix8x8 res;
	for(int i=0;i<8;i++){
		res[0][i]=sqrt(2.0)/4.0;
	}
	for(int i=1;i<8;i++){
		for(int j=0;j<8;j++){
			res[i][j]=cos(i*(2.0*j+1.0)/16.0*M_PI)/2.0;
		}
	}
	return res;
}

const Matrix8x8 Matrix8x8::DCTMatrix = DCTM();
Matrix8x8 cuantificar(const Matrix8x8& m, const Matrix8x8& q){
	Matrix8x8 res;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			res[i][j]=floor(0.5+m[i][j]/q[i][j]);
		}
	}
	return res;
}