#include "imagen/imagen.h"        //Exportacion de resultados
#include "delaunay.h"   	   	  //Para calcular triangulacionaciones
#include "geometria.h"			  //Operaciones con puntos


template<class T>
class VoronoiNoGeometrico{
private:
	std::vector<_2D::Punto<T>> puntos;
	int x, y;
	int n, m;
	Imagen grafica;
	T (*func)(const _2D::Punto<T>&,const _2D::Punto<T>&);
public:
	VoronoiNoGeometrico(){	
	}
	VoronoiNoGeometrico(int x, int y,const std::vector<_2D::Punto<T>>& v, T (*f_dist)(const _2D::Punto<T>&,const _2D::Punto<T>&)){
		this->x = x;
		this->y = y;
		grafica = obtenerImagen();		
		puntos = v;
		this->func = f_dist;
	}

	Imagen obtenerImagen(){
		Imagen I(x,y);		
		for(int i=0;i<y;i++){
			for(int j=0;j<x;j++){
				T dist_min = x*y*x*y;
				int id = 0;
				_2D::Punto<T> actual(j,i);
				for(int k=0;k<puntos.size();k++){
					T dist = func(actual,puntos[k]);
					if(dist<dist_min){
						dist_min = dist;
						id=k;
					}
				}
				try{
					I.en((int)actual.y,(int)actual.x)  =Color::hsl(113*id);
				}catch(...){

				}
					
			}
		}

		for(auto p:puntos){
			I.en((int)p.y,(int)p.x) = Color::rojo;
		}

		return I-I.laplace().umbral(1,Color::negro, Color::blanco);
	}
	
};

template<class T>
class Voronoi{
private:
	//puntos de entrada
	std::vector<_2D::Punto<T>> puntos;
	
	//Calculo de la triangulacion
	Delaunay<T> delaunay;
	std::vector<_2D::Triangulo<T>> triangulos;
	std::vector<_2D::Punto<T>> centrosCT;


	//Calculo de las regiones
	std::vector<std::vector<bool>> G; //Grafo que representa si 2 triangulos tienen un lado en comun
	std::vector<_2D::Linea<T>> lineas; //Lineas del diagrama
	
public:
	void agregaPunto(const _2D::Punto<T>& p){
		delaunay.agregaPunto(p);
	}


	std::vector<_2D::Punto<T>> damePuntos(){
		return puntos;
	}

	std::vector<_2D::Linea<T>> dameLineas(){
		return lineas;
	}

	std::vector<std::vector<bool>> dameGrafo(){
		return G;
	}

	std::vector<std::vector<bool>> dameGrafoTriangulacion(){
		return delaunay.dameGrafo();
	}

	void calcular(){
		delaunay.calcular();
		triangulos = delaunay.dameTriangulos();
		//inicializacion del grafo
		G = std::vector<std::vector<bool>>(triangulos.size(),std::vector<bool>(triangulos.size(),false));	
		//Calculo de los triangulos adyacentes
		for(int i=0;i<triangulos.size();i++){
			for(int j=i+1;j<triangulos.size();j++){
				if(comparteLado(triangulos[i],triangulos[j])){
					G[i][j]=G[j][i]=true;
				}
			}
		}	
		for(auto t: triangulos){
			centrosCT.push_back(_2D::Circulo<T>(t.p1,t.p2,t.p3).centro);
		}

		for(int i=0;i<G.size();i++){
			for(int j=i+1;j<G.size();j++){
				if(G[i][j]){
					lineas.push_back(_2D::Linea<T>(centrosCT[i],centrosCT[j]));
				}
			}
		}
			
	}
};
