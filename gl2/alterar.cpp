#include "imagen/imagen.h"
int main(){
	Imagen I;
	I.leeBMP("ciudadv1.bmp");
	I = I.escalaDeGrises().laplace().umbral(200,Color::negro,Color::blanco);
	I.guardaBMP("ciudadv1bn.bmp");
}