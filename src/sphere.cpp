// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:sphere.cpp
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

#ifndef SPHERE_CPP
#define SHPERE_CPP

#include "sphere.h"
#include <cmath>


float Sphere::intersects(const ray& r)  {

	vec3 dist = center - r.pos; 
	float B = r.direction * dist;
    
    float D = B*B - dist * dist + radius * radius; 
    if (D < 0.0) 
        return NO_INTERSECTION; 
    float t0 = B - sqrt(D); 
    float t1 = B + sqrt(D);

	float rs = NO_INTERSECTION; 
	if (t0 >= EPSILON ){
		rs = t0;
	}
	if (t1 >= EPSILON){
		if (rs == NO_INTERSECTION) rs = t1;
		else 
			rs = std::min(rs,t1);
	}
	

	return rs;
}

vec3 Sphere::getLightPoint(){
	float x,y,z,t;
	z = ( urandom() * 2 ) - 1;  //random uniform between -1, 1
	t = ( urandom() * 2 * M_PI); //random uniform between 0, 2pi

	x= sqrtf(1.0f - (z*z)) * cos(t);
	y= sqrtf(1.0f - (z*z)) * sin(t);

	vec3 p =  vec3(x,y,z)*radius + center;
	return p;
}


vec3  Sphere::normalAt(const vec3& p)  {
	return (p-center).normalize();
}
float Sphere::getArea(){
	return 4.0f*M_PI*radius*radius;
}


void Sphere::print(ostream& out) const{
	out<< "sphere: " 
	<< "c("           << center.x << "," 
					  << center.y << ","				          
					  << center.z << ") " 
	<< "r("           << radius << ") " 
	<< *material ;
}
ostream& operator<<(ostream& os,const Sphere& s){
	s.print(os);
	return os;
}

#endif 
