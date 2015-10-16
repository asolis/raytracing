// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:triangle.h
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

#ifndef TRIANGL_H
#define TRIANGL_H

#include "object.h"
#include <vector>


class Triangle: public Object{


	protected:
		float getArea();

	public:
		vec3  v[3];

		Triangle(){
			for (int i = 0 ; i < 3 ; i++){
				v[i] = vec3();
			}
		}
	
		float intersects(const ray& r) ;
		vec3 getLightPoint();
		void print(ostream& out) const;
		virtual vec3  normalAt(const vec3& p) ;
};

ostream& operator<<(ostream& os,const Triangle& s);

#endif
