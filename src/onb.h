// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:onb.h
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

#ifndef ONB_H
#define ONB_H

#define ONB_EPSILON 0.1f

#include "vec3.h"

class ONB{

	public:
		vec3 u,v,w;
		ONB():u(1,0,0),v(0,1,0),w(0,0,1){}
		ONB(vec3 _u, vec3 _v, vec3 _w): u(_u),v(_v),w(_w) {}
		
		static ONB initFromW(const vec3& _w) {
			vec3 n(1.0,   0, 0);
			vec3 m(  0, 1.0, 0);
			vec3 w = _w.normalize();
			vec3 u = w.cross(n);
			if (u.length() < ONB_EPSILON)
				u = n.cross(m);
			vec3 v = w.cross(u);
			return ONB(u,v,w);
		}
		vec3 getVecInONB(float _u, float _v, float _w){
			return vec3(_u*u + _v*v + _w*w);
		}
		vec3 getVecInONB(vec3& v){
			return vec3(v.x*u + v.y*v + v.z*w);
		}
};


#endif
