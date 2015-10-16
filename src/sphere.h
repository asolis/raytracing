// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:sphere.h
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

#ifndef SPHERE_H
#define SPHERE_H


#include <ostream>
#include "object.h"



using std::ostream;
using std::endl;

class Sphere :public Object{

	protected:
		float getArea();
	public:
		vec3     center;
		float    radius;
		Sphere(): center(0,0,0), radius(0){}
		
		float intersects(const ray& r) ;
		void print(ostream& out) const;
		vec3 getLightPoint();
		vec3 normalAt(const vec3& p) ;
};

ostream& operator<<(ostream& os,const Sphere& s);

#endif
