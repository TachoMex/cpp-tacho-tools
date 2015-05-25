#include <GL/freeglut.h> 
#include <GL/gl.h> 
#include "imagen/imagen.h"
#include "gl2.h"
Imagen i;

void renderFunction(){
	glDrawPixels(i);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv){ 
	if(argc!=2){
		return 0;
	}

	i.leeBMP(argv[1]);
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(i.columnas(),i.filas()); 
	glutInitWindowPosition(0,0); 
	glutCreateWindow(argv[1]); 
	glClearColor(0, 0,0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glClear(GL_COLOR_BUFFER_BIT); 
	gluOrtho2D(0, 0, i.columnas(), i.filas()); 
	glFlush(); 
	glutDisplayFunc(renderFunction); 
	glutMainLoop(); 
	return 0; 
} 