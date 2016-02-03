// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:onb.h
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
