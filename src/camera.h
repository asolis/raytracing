// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:camera.h
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

#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class Camera {
	
	public:
		vec3 up;
		vec3 direction;
		vec3 center;
		vec2 resolution;
		float flength;
		Camera(): up(),
				  direction(),
				  center(),
				  resolution(),
				  flength(0.0){}

		ray getRay(float x, float y);
};

ostream& operator<<(ostream& os,const Camera& f);

#endif
