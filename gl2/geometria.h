#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "3D/linea.h"
#include "3D/punto.h"
#include "3D/prisma.h"
#include "3D/angulo.h"

#include "2D/linea.h"
#include "2D/punto.h"
#include "2D/rectangulo.h"

#include "4D/punto.h"
#include "4D/linea.h"

_2D::punto conversionParalela(_3D::punto desde, _3D::punto hacia, _3D::punto arriba, _3D::punto p){
	p = _3D::puntoDeVista(desde,hacia,arriba,p);
	return _2D::punto(p.x,p.y);
}

_3D::punto conversionParalela(_4D::punto desde, _4D::punto hacia, _4D::punto arriba, _4D::punto sobre, _4D::punto  p){
	p = _4D::puntoDeVista( desde,  hacia,  arriba,  sobre, p);
	return _3D::punto(p.x, p.y, p.z);
}

_2D::linea conversionParalela(_3D::punto desde, _3D::punto hacia, _3D::punto arriba, _3D::linea l){
	return _2D::linea(conversionParalela(desde, hacia, arriba, l.inicio), conversionParalela(desde, hacia, arriba, l.fin));
}

_3D::linea conversionParalela(_4D::punto desde, _4D::punto hacia, _4D::punto arriba, _4D::punto sobre, _4D::linea l){
	return _3D::linea(conversionParalela(desde,hacia,arriba,sobre,l.inicio), conversionParalela(desde,hacia,arriba,sobre,l.fin));
}

#endif