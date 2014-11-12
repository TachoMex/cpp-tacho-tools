#include <GL/freeglut.h>
#include <GL/gl.h>
#include "imagen/imagen.h"
#include "geometria.h"
#include "primitivas.h"
#include "gl2.h"
using namespace std;
using namespace _2D;
imagen I;

bool pausa;
linea l;
double ang;
double ang2;
double ang3;
double ang4;
punto ant;
punto inicial;
int anguloColor=0;
double dang[10];

void renderFunction(){
	linea l2(l.fin,120,ang);
	linea l3(l2.fin,100, ang2);
	//linea l4(l3.fin, 50, ang3);
	//linea l5(l4.fin, 100, ang4);
	I.draw();
	if(pausa){
		return;
	}
	l=l.rotar(dang[0]);
	ang+=dang[1];
	ang2+=dang[2];
	//ang3-=0.0123;
	//ang4+=0.2223;
	dibujaLinea(I,ant.x, ant.y, l3.fin.x, l3.fin.y, color::blanco);
	ant=l3.fin;
	//I.read();
    glColor(color::azul);
	glDraw(l,1);
	glColor(color::verde);
	glDraw(l2,1);
	glColor(color::amarillo);
	glDraw(l3,1);
/*	glColor(color::cyan);
	glDraw(l4);
	glColor(color::rojo);
	glDraw(l5);
	glColor(color::gris);*/
	primitivas::circulo(l.inicio.x, l.inicio.y, l.longitud(), 1);
	glColor(color::naranja);
	primitivas::circulo(l2.inicio.x, l2.inicio.y, l2.longitud(), 1);
	glColor(color::morado);
	primitivas::circulo(l3.inicio.x, l3.inicio.y, l3.longitud(), 1);
	glColor(color::cafe);
	/*
	primitivas::circulo(l4.inicio.x, l4.inicio.y, l4.longitud());
	glColor(color::azul*0.7);
	primitivas::circulo(l5.inicio.x, l5.inicio.y, l5.longitud());
*/
	glFlush();
	glutSwapBuffers();
	if(distancia(ant, inicial)<0.5){
		//cout<<ant.toString()<<inicial.toString()<<endl;
		//cout<<distancia(ant, inicial)<<endl;
		I.guardaBMP("rosa.bmp");
		//exit(0);
	}
	

	glutTimerFunc(0, (void(*)(int))renderFunction, 0);
}

void eventoTeclado(unsigned char k, int x, int y){
	//cout<<k<<endl;

	if(k=='a'){
		I.draw();
		glFlush();
	}else if(k=='g'){
		I.guardaBMP("rosa.bmp");
	}else if(k<='9' and k>='0'){
		dang[k-'0']+=0.001;
	}else if(k=='r'){
		I=imagen(800,800,color::negro);
	}else if(k=='p'){
		pausa^=true;
		glutTimerFunc(0,(void(*)(int))renderFunction,0);
	}

}


int main(int argc, char** argv){
	l=linea(punto(400,400),punto(500,400));
	ant=inicial=punto(720,400);
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Rosas");
	glClearColor(0,0,0, 0.0);
	glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800); 
	glFlush();
	I.read();
	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(eventoTeclado);
	glutMainLoop();   
	return 0;
}