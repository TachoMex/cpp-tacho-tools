#include <GL/freeglut.h>
#include <GL/gl.h>
#include "imagen/imagen.h"
#include "geometria.h"
#include "primitivas.h"
#include "gl2.h"

const int X_SIZE = 600;
const int Y_SIZE = 600;

using namespace std;
using namespace _2D;
Imagen I;

bool pausa;
bool trazo;

Punto<double> ant;
Punto<double> centro;
double dang[10];
double ang[10];
double longitudes[10];


void renderFunction(){
	glDrawPixels(I);
	int colorLinea=0;
	Punto<double> pendulo=centro;
	for(int i=0;i<10;i++){
		glColor(Color::hsl(20*i));
		Linea<double> l(pendulo, pendulo+Punto<double>::polar(longitudes[i],ang[i]));
		glDraw(l,1);
		glColor(Color::hsl(20*i+10));
		primitivas::circulo(pendulo.x, pendulo.y, longitudes[i],1);
		pendulo=l.fin;
		if(not pausa)
		ang[i]+=dang[i];
	}
	if(not trazo)
	dibujaLinea(I,ant.x, ant.y, pendulo.x, pendulo.y, Color::blanco);
	ant=pendulo;
	glFlush();
	glutSwapBuffers();
	glutTimerFunc(0, (void(*)(int))renderFunction, 0);
}

void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case '1': 
			dang[0]+=0.001;
		break;
		case 'q':
			dang[0]-=0.0001;
		break;
		case 'a':
			longitudes[0]++;
		break;
		case 'z':
			longitudes[0]--;
		break;

		case '2': 
			dang[1]+=0.001;
		break;
		case 'w':
			dang[1]-=0.0001;
		break;
		case 's':
			longitudes[1]++;
		break;
		case 'x':
			longitudes[1]--;
		break;

		case '3': 
			dang[2]+=0.001;
		break;
		case 'e':
			dang[2]-=0.0001;
		break;
		case 'd':
			longitudes[2]++;
		break;
		case 'c':
			longitudes[2]--;
		break;

		case '4': 
			dang[3]+=0.001;
		break;
		case 'r':
			dang[3]-=0.0001;
		break;
		case 'f':
			longitudes[3]++;
		break;
		case 'v':
			longitudes[3]--;
		break;

		case '5': 
			dang[4]+=0.001;
		break;
		case 't':
			dang[4]-=0.0001;
		break;
		case 'g':
			longitudes[4]++;
		break;
		case 'b':
			longitudes[4]--;
		break;

		case '6': 
			dang[5]+=0.001;
		break;
		case 'y':
			dang[5]-=0.0001;
		break;
		case 'h':
			longitudes[5]++;
		break;
		case 'n':
			longitudes[5]--;
		break;

		case '7': 
			dang[6]+=0.001;
		break;
		case 'u':
			dang[6]-=0.0001;
		break;
		case 'j':
			longitudes[6]++;
		break;
		case 'm':
			longitudes[6]--;
		break;

		case '8': 
			dang[7]+=0.001;
		break;
		case 'i':
			dang[7]-=0.0001;
		break;
		case 'k':
			longitudes[7]++;
		break;
		case ',':
			longitudes[7]--;
		break;

		case 16:
			pausa^=true;
			glutTimerFunc(0,(void(*)(int))renderFunction,0);
		break;
		case 3:
			I=Imagen(800, 800, Color::negro);
		break;
		case 7:
			I.guardaBMP("rosas.bmp");
		break;
		case 18:
			for(int i=0;i<10;i++){
				longitudes[i]=0;
				dang[i]=0;
				ang[i]=0;
			}
		break;

		case 20: 
			trazo^=true;
		break;
		default:
			cout<<(int)k<<endl;
	}

}


int main(int argc, char** argv){
	centro=ant=Punto<double>(X_SIZE/2,Y_SIZE/2);
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(X_SIZE,Y_SIZE);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Rosas");
	glClearColor(0,0,0, 0.0);
	glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,X_SIZE,0,Y_SIZE); 
	glFlush();
	glReadPixels(I);
	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(eventoTeclado);
	glutMainLoop();   
	return 0;
}