#include "imagen/imagen.h"
using namespace std;
int main(int argc, char** argv){
	if(argc==2){
		Imagen I;
		I.leerBMP(argv[1]);
		I=I.laplace().umbral(10,Color::negro, Color::blanco);
		I.guardaBMP((string(argv[1]).substr(0)+"sobel.bmp").c_str());
	}
}