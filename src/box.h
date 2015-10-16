// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:box.h
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

#ifndef BOX_H
#define BOX_H

#include "material.h"
#include "object.h"
#include "plane.h"


class Box: public Object {
	
	protected:
		float getArea();
	private:
		int  face;		
	public :
		Plane  p[6];
		Box(){
			for (size_t i = 0 ; i < 6 ; i++){
				p[i] = Plane();
			}
			filled = false;
			face = -1;
		}
		    // Bottom, 1, 2, 3, 4, Top - 1,2,3,4 counter clockwise faces starting from Bottom.V0 - Bottom.V1
		
		float intersects(const ray& r) ;
		void fill();
		void print(ostream& out) const;

		Material* getMaterial();
		
		vec3 normalAt(const vec3& p) ;
		vec3 getLightPoint(); 
		
};

ostream& operator<<(ostream& os,const Box& f);

#endif 
