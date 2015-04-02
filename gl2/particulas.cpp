#include "geometria.h"
#include "imagen/color.h"
#include "gl2.h"
#include <vector>
using namespace std;
using namespace _2D;
const int SCREEN_X = 800;
const int SCREEN_Y = 600;
const char * WINDOW_NAME = "Particulas";
const double g=0.05;
const int radio=5;
const Punto<double> centroSol(SCREEN_X/2, SCREEN_Y/2);

class particula{
	public:
		Punto<double> posicion;
		Punto<double> velocidad;
		Punto<double> aceleracion;	
		static double dt;
	private:
		Color col;

	public:
		particula(){

		}
		particula(const Punto<double>& p,const Punto<double>& v,const Punto<double>& a,const Color& c){
			posicion=p;
			velocidad=v;
			aceleracion=a;
			col=c;
		}
		particula(const Punto<double>& p, const Color& c):velocidad(),aceleracion(){
			posicion=p;
			col=c;
		}

		void iterar(){
			posicion+=velocidad*dt;
			velocidad+=aceleracion*dt;
		}

		void dibujar(){
			glColor(col);
			glDraw(posicion);
		}
};

double particula::dt = 0.01;

vector<particula> v;

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor(Color::amarillo);
	for(int i=-radio;i<=radio;i++){
		for(int j=-radio;j<=radio;j++){
			if(i*i+j*j <= radio*radio + radio/2){
				glDraw(centroSol+Punto<double>(i,j));
			}
		}
	}

	for(particula& p: v){
		Punto<double> dist = centroSol - p.posicion;
		double r = dist.norma2();

		p.dibujar();
		p.aceleracion+=(dist)*(1.0/r)*particula::dt*g;
		p.iterar();
	}



	glFlush();
	glutSwapBuffers();
	glutTimerFunc(1, (void(*)(int))renderFunction,0);
}

void eventoClick(int b , int e, int x, int y){
	v.push_back(particula(Punto<double>(x, SCREEN_Y-y),Punto<double>(0.5,0), Punto<double>(0,0),Color::hsl(v.size()*7)));
}

void eventoArrastre(int x, int y){

}

void eventoTeclado(unsigned char k, int x, int y){ 
	switch(k){
	} 
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
	gluOrtho2D(0, SCREEN_X, 0, SCREEN_Y); 
	glFlush(); 
	glutMouseFunc(eventoClick); 
	glutMotionFunc(eventoArrastre); 
	glutDisplayFunc(renderFunction); 
	glutKeyboardFunc(eventoTeclado); 
	glutMainLoop(); 
	return 0; 
} 