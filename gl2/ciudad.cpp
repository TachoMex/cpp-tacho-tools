#include <iostream>               //Entradas y salidas debugging
#include "imagen/imagen.h"        //Exportacion de resultados
#include "imagen/primitivas.h"    //Exportacion de resultados
#include "voronoi.h"   	   	      //Para calcular triangulacionaciones
#include "gl2.h"				  //Interfaz
#include <cstdlib> 				  //Random
#include <chrono>				  //Debugging con sleeps
#include <thread>				  //Debugging con sleeps
using namespace std;
using namespace _2D;

typedef double llint;

const int SCREEN_X = 1000;
const int SCREEN_Y = 1000;
const char * WINDOW_NAME = "VCities";
const int ANCHURA_MANZANAS = 7;
const int LARGO_MANZANAS = 15;




class interfaz{
private:
	//Datos de entrada
	Punto<int> tam;
	Punto<int> tamMat;
	Voronoi<llint> voronoi;
	vector<Punto<llint>> puntos; //Puntos generados

	//resultados
	vector<vector<bool>> triangulacion; //Grafo que representa 2 puntos deben conectarse segun la triangulacion de delaunay
	vector<Linea<llint>> lineas;		    //Lineas del diagrama
	vector<Poligono<llint>> regiones;   //Poligonos de las regiones del diagrama de voronoi


public:
	bool grafica_puntos;
	bool grafica_voronoi;
	interfaz(){	
	}
	interfaz(int x, int y, int n, int m){
		grafica_voronoi  = grafica_puntos = true;
		tam = Punto<int>(x,y);
		tamMat = Punto<int>(n,m);
		int dx = x/n;
		int dy = y/m;


		//Generacion de los puntos aleatorios
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				voronoi.agregaPunto(Punto<llint>(dx*i+rand()%dx,dy*j+rand()%dy));
			}
		}


		voronoi.calcular();
		puntos=voronoi.damePuntos();
		lineas=voronoi.dameLineas();
		triangulacion=voronoi.dameGrafoTriangulacion();	
		regiones = voronoi.regiones();
		int tam = regiones.size();
		int i=0;
		for(auto region: regiones){
			Voronoi<llint> ciudad;
			for(auto p: puntos){
				ciudad.agregaPunto(p);
			}
			RectanguloGirado<llint> r = region.rectanguloRecubridorMinimo();
			Punto<llint> centro = r.centro();
			for(llint x = r.inicio.x+ANCHURA_MANZANAS; x<r.fin.x; x+=ANCHURA_MANZANAS){
				for(llint y = r.inicio.y+LARGO_MANZANAS; y<r.fin.y; y+=LARGO_MANZANAS){
					Punto<llint> p(x,y);
					p = (p-centro).rotar(r.angulo)+centro;
					if(region.contiene(p)){
						ciudad.agregaPunto(p);
					//	cout<<":P"<<endl;
					}
				}
			}
			ciudad.calcularRegiones(false);
			cout<<"Region: "<<i++<<"/"<<tam<<"::"<<ciudad.cantidadPuntos()<<endl;
			if(ciudad.cantidadPuntos()<350){	
				ciudad.calcular();
			}
			vector<Linea<llint>> temp=ciudad.dameLineas();
			glClear(GL_COLOR_BUFFER_BIT);
			glColor(Color::verde);
			glDraw(temp);
			glutSwapBuffers();
			glFlush();
			this_thread::sleep_for(chrono::seconds(1));		
			lineas.insert(lineas.end(),temp.begin(), temp.end());
		}
		cout<<"Fin"<<endl;
	}


	void dibujar(){
		cout<<"Inicia dibujo"<<endl;
		cout<<"Cantidad de lineas: "<<lineas.size()<<endl;
		glClear(GL_COLOR_BUFFER_BIT);
		if(grafica_voronoi){
			int k=0;
			glColor(Color::verde);
			glDraw(lineas);		
		}
		if(grafica_puntos){
			glColor(Color::rojo);
			glDraw(puntos,5);
		}
		/*
		int k=0;
		Imagen I;
		glReadPixels(I);
		for(auto region: regiones){
			glDrawPixels(I);
			glColor(Color::azul);
			glDraw(region);		
			glColor(Color::morado);
			glDraw(region.rectanguloRecubridorMinimo());
			glutSwapBuffers();
			glFlush();
			this_thread::sleep_for(chrono::seconds(1));
		}
		*/
		glutSwapBuffers();
		glFlush();
	}
};

interfaz vs;

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	vs.dibujar();
	glFlush();
	glutSwapBuffers();
}

void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case 'p':
			vs.grafica_puntos^=true;
			break;
		case 'v':
			vs.grafica_voronoi^=true;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){ 
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(SCREEN_X,SCREEN_Y); 
	glutInitWindowPosition(0,0); 
	glutCreateWindow(WINDOW_NAME); 
	glClearColor(0, 0,0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glClear(GL_COLOR_BUFFER_BIT); 
	gluOrtho2D(0, SCREEN_X, 0,SCREEN_Y); 
	glFlush(); 
	glutDisplayFunc(renderFunction); 
	glutKeyboardFunc(eventoTeclado); 
	srand(time(NULL));
	vs = interfaz(SCREEN_X,SCREEN_Y,7,7);
	glutMainLoop(); 
	return 0; 
} 


