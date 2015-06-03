#include "voronoi.h"
#include <complex>
using namespace std;
using namespace _2D;


const int TAM_X = 600;
const int TAM_Y = 600; //600 -> 3, 100 : 0.5


int main(){

	vector<Punto<double>> p;


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


	

	mat.guardaBMP("testvm.bmp");

	return 0;
}
