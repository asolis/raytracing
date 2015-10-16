// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:frame.h
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

#ifndef FRAME_H
#define FRAME_H

#include "object.h"

class Frame: public Object {
	protected:
		float getArea();
	
	public :
		vec3  v[3];
		vec2  h[3];
		Frame(){
			for (size_t i = 0 ; i < 3 ; i++){
				v[i] = vec3();
				h[i] = vec2();
			}
		}

		
		float intersects(const ray& r) ;
		vec3 getLightPoint();
		void print(ostream& out) const;
		vec3  normalAt(const vec3& p) ;
};

ostream& operator<<(ostream& os,const Frame& f);


#endif
