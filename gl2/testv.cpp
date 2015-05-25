#include "voronoi.h"
#include <complex>
using namespace std;
using namespace _2D;


const int TAM_X = 1000;
const int TAM_Y = 500; //600 -> 3, 100 : 0.5
const int iteraciones = 80;

const double Xi = -2.0-1;
const double Yi = -1.25;
const double Xf =  2.0;
const double Yf =  1.25;
const double limite = 2.0;

complex<double> itera(complex<double> z, complex<double> c){
	return z*z+c;
	//return pow(z,6)+pow(c,-1);
	//return cos(z)+pow(c,-1);
}

int main(){

	vector<Punto<double>> p;
	double dx = (Xf-Xi)/TAM_X;
	double dy = (Yf-Yi)/TAM_Y;


	for(int j=0;j<20;j++){
		for(int i=0;i<20;i++){
			p.push_back(Punto<double>(400,250)+Punto<double>::polar(200/5*(j+1),M_PI*i/10.0+M_PI/(20)*j));
		}
	}

	for(int j=0;j<9;j++){
		for(int i=0;i<20;i++){
			p.push_back(Punto<double>(400,250)+Punto<double>::polar(50/5*(j+1),M_PI*i/10.0+M_PI/(20)*j));
		}
	}

	VoronoiNoGeometrico<double> v(TAM_X,TAM_Y,p,distanciaM);
	Imagen mat=v.obtenerImagen();


	for(int i=0;i<TAM_X;i++){
		for(int j=0;j<TAM_Y;j++){
			double x = Xi + dx*i;
			double y = Yi + dy*j;
			complex<double> z, c(x,y);
			int k;
			for(k = 0; k < iteraciones; k++){
				if(abs(z)>=limite){
					break;
				}
				z = itera(z,c);
			}
			double luz = ((double)k/iteraciones)+log((double)i/(abs(i-500)+4))*0.05;
			luz = min(luz,1.0);
			mat.en(j,i) = mat.en(j,i)*luz;

		}
	}


	mat.guardaBMP("testvm.bmp");

	return 0;
}
