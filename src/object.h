// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:object.h
/**************************************************************************************************
 **************************************************************************************************
 
     BSD 3-Clause License (https://www.tldrlegal.com/l/bsd3)
     
     Copyright (c) 2012 Andrés Solís Montero <http://www.solism.ca>, All rights reserved.
     
     
     Redistribution and use in source and binary forms, with or without modification,
     are permitted provided that the following conditions are met:
     
     1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.
     2. Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the documentation
        and/or other materials provided with the distribution.
     3. Neither the name of the copyright holder nor the names of its contributors
        may be used to endorse or promote products derived from this software
        without specific prior written permission.
     
     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
     AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
     IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
     ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
     LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
     DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
     THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
     OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
     OF THE POSSIBILITY OF SUCH DAMAGE.
 
 **************************************************************************************************
 **************************************************************************************************/

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
