#include <iostream>
#include <queue>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "geometria.h"
#include "imagen/imagen.h"
#include <vector>
using namespace _2D;
using namespace std;

class nube{
	private:
		int tx, ty;
		vector<vector<int>> colores;
	public:


		nube(int x, int y, int seed1, int seed2, int seed3, int seed4, int (*func)(int), int (*aleatoria)(int)){
			tx=x+1;
			ty=y+1;
			int iteraciones=11;
			x--;
			y--;
			colores = vector<vector<int>>(tx,vector<int>(ty));

			queue<linea<int> > q;
			q.push(linea<int>(punto<int>(0,0), punto<int>(x, y)));
			colores[0][0]=seed1;
			colores[x][0]=seed2;
			colores[0][y]=seed3;
			colores[x][y]=seed4;

			for(int i=0;i<iteraciones;i++){
				int n = q.size();
				for(int j=0;j<n;j++){
					linea<int> l = q.front();
					q.pop();
					//#0#
					//123
					//#4#
					punto<int> centros[5];
					centros[0] = punto<int>((l.inicio.x+l.fin.x)/2,l.inicio.y); 
					centros[1] = punto<int>(l.inicio.x,(l.fin.y+l.inicio.y)/2); 
					centros[2] = punto<int>((l.inicio.x+l.fin.x)/2,(l.fin.y+l.inicio.y)/2); 
					centros[3] = punto<int>(l.fin.x,(l.inicio.y+l.fin.y)/2); 
					centros[4] = punto<int>((l.inicio.x+l.fin.x)/2,l.fin.y); 
					int longitud = (l.fin-l.inicio).norma2();

					if(colores[centros[0].x][centros[0].y]<0)
						colores[centros[0].x][centros[0].y]=(colores[l.inicio.x][l.inicio.y]+colores[l.fin.x][l.inicio.y])/2+aleatoria(longitud);
					if(colores[centros[1].x][centros[1].y]<0)
						colores[centros[1].x][centros[1].y]=(colores[l.inicio.x][l.inicio.y]+colores[l.inicio.x][l.fin.y])/2+aleatoria(longitud);
					if(colores[centros[2].x][centros[2].y]<0)
						colores[centros[2].x][centros[2].y]=(colores[l.inicio.x][l.inicio.y]+colores[l.inicio.x][l.fin.y]+colores[l.fin.x][l.fin.y]+colores[l.fin.x][l.fin.y])/4+aleatoria(longitud);
					if(colores[centros[3].x][centros[3].y]<0)
						colores[centros[3].x][centros[3].y]=(colores[l.fin.x][l.inicio.y]+colores[l.fin.x][l.fin.y])/2+aleatoria(longitud);
					if(colores[centros[4].x][centros[4].y]<0)
						colores[centros[4].x][centros[4].y]=(colores[l.inicio.x][l.fin.y]+colores[l.fin.x][l.fin.y])/2+aleatoria(longitud);
					q.push(linea<int>(l.inicio,centros[2]));
					q.push(linea<int>(centros[0],centros[3]));
					q.push(linea<int>(centros[1],centros[4]));
					q.push(linea<int>(centros[2],l.fin));
				}
			}
		}

		imagen construye(){
			imagen I(tx, ty);
			for(int i=0;i<tx;i++){
				for(int j=0;j<ty;j++){
					I(i,j)=color::blanco*(double(colores[i][j])/1000);
				}	
			}
			return I;
		}


};

int main(){
	srand((unsigned)time(NULL));
	nube nub(600,600, 0, 50, 120, 1000, [](int distancia){return (rand()%2?1:-1)*rand()%(distancia/100000)*0;}, NULL );
	imagen I = nub.construye();
	cout<<":v"<<endl;
	I.guardaBMP("nube.bmp");
	return 0;
}

