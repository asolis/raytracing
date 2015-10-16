// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:disc.h
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

#ifndef DISC_H
#define DISC_H

#include <ostream>
#include "object.h"
#include "onb.h"

using std::ostream;
using std::endl;

class Disc: public Object {
		
		protected:
		float getArea();
	
		public :
		vec3     center;
		float    radius; 
		vec3     normal;
		Disc(): center(0,0,0), normal(0,0,0), radius(0) {}

		
		float intersects(const ray& r) ;
		void print(ostream& out) const;
		vec3 getLightPoint();
		vec3  normalAt(const vec3& p) ;
};


ostream& operator<<(ostream& os,const Disc& s);

#endif 
