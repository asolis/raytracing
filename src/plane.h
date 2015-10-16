// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:plane.h
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

#ifndef PLANE_H
#define PLANE_H


#include "object.h"

class Plane: public Object {

	protected:
		float getArea();
	
	private:
		vec3 n;
		bool hasN;

	public :
		vec3  v[3]; 
		Plane(){
			for (int i = 0 ; i < 3 ; i++){
				v[i] = vec3();
			}
			hasN = false;
		}

		
		float intersects(const ray& r) ;
		void print(ostream& out) const;
		vec3 getLightPoint();
		vec3  normalAt(const vec3& p) ;
};


ostream& operator<<(ostream& os,const Plane& s);


#endif 
