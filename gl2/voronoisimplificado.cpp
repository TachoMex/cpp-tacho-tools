#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "geometria.h"
#include "imagen/imagen.h"
#include "gl2.h"
#include <vector>
#include <cstdlib>
#include <set>
#include <map>
using namespace std;
using namespace _2D;

typedef long long int llint;

const int SCREEN_X = 600;
const int SCREEN_Y = 600;
const char * WINDOW_NAME = "Voronoi";

class voronoi_simple{
private:
	punto<llint> tam;
	punto<llint> tamMat;
	vector<punto<llint>> puntos;
	vector<punto<llint>> centros;
	vector<punto<int>> triangulacion;
public:
	bool cuadricula;
	bool grafica_puntos;
	bool grafica_triangulacion;
	voronoi_simple(){	
	}
	voronoi_simple(int x, int y, int n, int m){
		cuadricula = grafica_puntos = grafica_triangulacion = true;
		tam = punto<llint>(x,y);
		tamMat = punto<llint>(n,m);
		int dx = x/n;
		int dy = y/m;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				puntos.push_back(punto<llint>(dx*i+rand()%dx,dy*j+rand()%dy));
			}
		}

		vector<punto<int>> lineas;
		for(int i=0;i<puntos.size();i++){
			for(int j = i+1;j<puntos.size();j++){
				lineas.push_back(punto<int>(i,j));
			}
		}
		int k=0;
		sort(lineas.begin(), lineas.end(), [&](const punto<int>&a , const punto<int>&b){ return linea<llint>(puntos[a.x],puntos[a.y]).longitud2()<linea<llint>(puntos[b.x],puntos[b.y]).longitud2();});
		for(int i=0;i<lineas.size();i++){
			bool choca = false;
			for(int j=0;j<triangulacion.size();j++){
				if(linea<llint>(puntos[lineas[i].x],puntos[lineas[i].y]).colisiona(linea<llint>(puntos[triangulacion[j].x],puntos[triangulacion[j].y]))){
					choca = true;
					break;
				}
			}
			if(not choca){
				triangulacion.push_back(lineas[i]);
			}
		}


		
	}

	void dibujar(){
		int dx = tam.x/tamMat.x;
		int dy = tam.y/tamMat.y;
		if(cuadricula){
			glColor(color::blanco);
			for(int i=1;i<tamMat.x;i++){
				glDraw(linea<llint>(punto<llint>(i*dx,0),punto<llint>(i*dx,tam.y)));
			}
			for(int i=1;i<tamMat.y;i++){
				glDraw(linea<llint>(punto<llint>(0,i*dy),punto<llint>(tam.x,i*dy)));
			}
		}
		if(grafica_puntos){
			glColor(color::rojo);
			for(int i=0;i<puntos.size();i++){
				glDraw(puntos[i],5);
			}
		}
		if(grafica_triangulacion){
			int i=0;
			for(punto<int> l:triangulacion ){
				glColor(color::hsl(7*i++));
				glDraw(linea<llint>(puntos[l.x],puntos[l.y]));
				cout<<l.toString()<<endl;
			}
		}


	


	}
};

voronoi_simple vs;

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	vs.dibujar();
	glFlush();
	glutSwapBuffers();
}

void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case 'g':
			vs.cuadricula^=true;
			break;
		case 't':
			vs.grafica_triangulacion^=true;
			break;
		case 'p':
			vs.grafica_puntos^=true;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){ 
	srand(time(NULL));
	vs = voronoi_simple(SCREEN_X,SCREEN_Y,5,5);
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
	glutMainLoop(); 
	return 0; 
} 


