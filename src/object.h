// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:object.h
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

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <ostream>
#include "vec3.h"
#include "material.h"

using std::vector;
using std::endl;
using std::ostream;


class Object {
	
	protected:
		Material *material;
		bool   filled;
		float  _area;
		virtual float getArea()					= 0;
		Object():_area(0),filled(false),material(NULL){	}
	public:		
		virtual void  print(ostream& out) const = 0;
		virtual float intersects(const ray& r)  = 0;
		virtual vec3  normalAt(const vec3& p)   = 0;
		virtual vec3  getLightPoint()			= 0;
		

		virtual float Area() {
			if (!filled) {
				filled = true;
				_area = getArea();
			}
			return _area;
		}

		virtual Material* getMaterial(){
			return material;
		}

		bool isLight(){ 
			return material->emits();
		}
		friend class ConfigReader;

};

inline ostream& operator<<(ostream& os, const Object& o){
	o.print(os);
	return os;
}




#endif
