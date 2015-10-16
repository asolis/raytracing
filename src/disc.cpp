// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:disc.cpp
// ==========================================================================
// (C)opyright:
//   Andres Solis Montero
//   Student #: 5480589
//   SITE, University of Ottawa
//   800 King Edward Ave.
//   Ottawa, On., K1N 6N5
//   Canada.
//   http://www.site.uottawa.ca
// 
// Creator: asolis	(Andres Solis Montero)
// Email:   asoli094@uottawa.ca
// ==========================================================================

#ifndef DISC_CPP
#define DISC_CPP


#include "disc.h"

float Disc::intersects(const ray& r)  {

	vec3 N = normal;
	     N = N.normalize();

    float d = - ( N * center);
	float t = - ((r.pos*N )+d);
	float td= N * r.direction;

	if (td > 0.0 ) return NO_INTERSECTION;
	
	t *= (1.0f/td);

	if (t < EPSILON ) return NO_INTERSECTION;

	vec3 l = r.pos + t * r.direction;
	vec3 c = center;
	if (c.distanceSq(l) > (radius*radius)) return NO_INTERSECTION;
	return t;
}
vec3 Disc::getLightPoint()
{
	ONB onb = ONB::initFromW(normal);

	float u = urandom()*2.0f -1.0f;
	float v = urandom()*2.0f -1.0f;

	while ( sqrt((u)*(u) + (v)*(v)) > 1) {
		u = urandom()*2.0f -1.0f;
		v = urandom()*2.0f -1.0f;
	}

	vec3 lp = onb.getVecInONB( (u*radius), (v*radius),0);
	return lp + center;
}
vec3  Disc::normalAt(const vec3& p)  {
	vec3 N = normal;

	return N.normalize();
}

float Disc::getArea(){
	return 2.0f*M_PI*radius*radius;
}
void Disc::print(ostream& out) const{
	out<< "disc: " 
	<< "c("           << center.x << "," 
					  << center.y << ","				          
					  << center.z << ") " 
	<< "n("           << normal.x << "," 
					  << normal.y << ","				          
					  << normal.z << ") " 
	<< "radius("      << radius << ") "
	<< *material;
}
ostream& operator<<(ostream& os,const Disc& s){
	s.print(os);
	return os;
}


#endif
