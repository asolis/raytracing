// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:camera.cpp
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

#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.h"
using std::endl;


ray Camera::getRay(float x, float y){
	ray r;

	vec3 w   = -1.0f * direction.normalize();
	vec3 v   = up.normalize();
	vec3 u   = w.cross(v);

	float cu = x - .5f*resolution.x;
	float cv = y - .5f*resolution.y;

	vec3 Pij = center + cu * u  + cv * v;

	if (flength == 0) {
		r.pos = Pij;
		r.direction = -1.0*w;
		return r;
		
	}

	vec3 E   = center + flength * w;
	

	r.pos = E;
	r.direction = (Pij - E).normalize();
	return r;
}


ostream& operator<<(ostream& os,const Camera& s){
	os  << "camera:  " << endl
		<< "\tcenter("         << s.center.x  << ","
						<< s.center.y  << ","
						<< s.center.z  << ") " ;
	os	<< "\tup("        << s.up.x  << ","
						<< s.up.y  << ","
						<< s.up.z  << ") " ;
	os	<< "\tdir("       << s.direction.x  << ","
						<< s.direction.y  << ","
						<< s.direction.z  << ") " <<endl; 
	os	<< "\tresolution("       << s.resolution.x  << ","
						       << s.resolution.y  << ") " ; 
	os	<< "\tflength("   << s.flength  << ") ";
	return os;
}

#endif 
