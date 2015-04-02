#include "geometria.h"
#include "imagen/color.h"
#include "imagen/imagen.h"
#include "STL2/cuaternion.h"
#include <queue>
#include <iostream>
#include "gl2.h"
using namespace std;

//punto camara(2,13,19);
_3D::Punto<double> cam3(10,10,10);
_4D::Punto<double> cam4(10,10,10,10);



void eventoTeclado(unsigned char k, int x, int y){
	Imagen M;
	switch(k){
		case 'q': cam3.z-=1; break;
		case 'a': cam3.x+=1; break;
		case 'w': cam3.y+=1; break;
		case 's': cam3.y-=1; break;
		case 'e': cam3.z+=1; break;
		case 'd': cam3.x-=1; break;
		case 'Q': cam4.z-=1; break;
		case 'A': cam4.x+=1; break;
		case 'W': cam4.y+=1; break;
		case 'S': cam4.y-=1; break;
		case 'E': cam4.z+=1; break;
		case 'D': cam4.x-=1; break;
		case 'Z': cam4.w-=1; break;
		case 'C': cam4.w+=1; break;
 		case 'k': cout<<cam3.toString()<<endl; break;
		case 'K': cout<<cam4.toString()<<endl; break;
		case ' ': 
			glReadPixels(M);
			M.guardaBMP("hipecubo.bmp");
		break;
	}
	glutPostRedisplay();
}

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	gluOrtho2D(-10,10,-10,10);
	
	_4D::Punto<double> x(10,0,0,0), y(0,10,0,0), z(0,0,10,0), w(0,0,0,10), o;
	_3D::Punto<double> x3= conversionParalela(cam4,_4D::Punto<double>(), _4D::Punto<double>(0,1,0,0), _4D::Punto<double>(0,0,1,0),x ); 
	_3D::Punto<double> y3= conversionParalela(cam4,_4D::Punto<double>(), _4D::Punto<double>(0,1,0,0), _4D::Punto<double>(0,0,1,0),y ); 
	_3D::Punto<double> z3= conversionParalela(cam4,_4D::Punto<double>(), _4D::Punto<double>(0,1,0,0), _4D::Punto<double>(0,0,1,0),z ); 
	_3D::Punto<double> w3= conversionParalela(cam4,_4D::Punto<double>(), _4D::Punto<double>(0,1,0,0), _4D::Punto<double>(0,0,1,0),w ); 
	_3D::Punto<double> o3= conversionParalela(cam4,_4D::Punto<double>(), _4D::Punto<double>(0,1,0,0), _4D::Punto<double>(0,0,1,0),o ); 
	_2D::Punto<double> x2 = conversionParalela(cam3,_3D::Punto<double>(), _3D::Punto<double>(0,1,0), x3);
	_2D::Punto<double> y2 = conversionParalela(cam3,_3D::Punto<double>(), _3D::Punto<double>(0,1,0), y3);
	_2D::Punto<double> z2 = conversionParalela(cam3,_3D::Punto<double>(), _3D::Punto<double>(0,1,0), z3);
	_2D::Punto<double> w2 = conversionParalela(cam3,_3D::Punto<double>(), _3D::Punto<double>(0,1,0), w3);
	_2D::Punto<double> o2 = conversionParalela(cam3,_3D::Punto<double>(), _3D::Punto<double>(0,1,0), o3);

	glColor(Color::rojo);

	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				for(int l=0;l<2;l++)
					for(int i2=0;i2<2;i2++)
						for(int j2=0;j2<2;j2++)
							for(int k2=0;k2<2;k2++)
								for(int l2=0;l2<2;l2++){
									_4D::Linea<double> li(_4D::Punto<double>(i*10,j*10, k*10, l*10), _4D::Punto<double>(i2*10,j2*10, k2*10, l2*10));
									if(li.longitud()==10)
										glDraw(conversionParalela(cam3, _3D::Punto<double>(), _3D::Punto<double>(0,1,0), conversionParalela(cam4, _4D::Punto<double>(), _4D::Punto<double>(0,1,0,0), _4D::Punto<double>(0,0,1,0), li)));
								}

					
				


	glBegin(GL_LINES);
		glVertex2f(o2.x,o2.y);
		glVertex2f(x2.x,x2.y);
		glVertex2f(o2.x,o2.y);
		glVertex2f(y2.x,y2.y);
		glVertex2f(o2.x,o2.y);
		glVertex2f(z2.x,z2.y);
		glVertex2f(o2.x,o2.y);
		glVertex2f(w2.x,w2.y);
	glEnd();
	glPopMatrix();
	glFlush();
}
int main(int argc, char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("3D");
	glClearColor(0, 0,0, 0.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(eventoTeclado);
	glutMainLoop();   

	return 0;
}