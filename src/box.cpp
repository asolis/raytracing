// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:box.cpp
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

#ifndef BOX_CPP
#define BOX_CPP

#include "box.h"


vec3 Box::getLightPoint(){

	//just to fill the gap... no a real implementation
	return p[1].getLightPoint();
}
float Box::intersects(const ray& r)  {
	fill();
	float re   = NO_INTERSECTION;
	float min  = NO_INTERSECTION;

	for (size_t i = 0 ; i < 6 ; i++){
		re = p[i].intersects(r);
		if (   (re != NO_INTERSECTION) &&  ( ( re < min) || (min == NO_INTERSECTION) ) ){
				min = re;
		}
	}
	return min;
}
Material* Box::getMaterial(){
	if (face ==-1) return material;
	else return p[face].getMaterial();
}

vec3  Box::normalAt(const vec3& _p)  {
	for (size_t i = 0 ; i < 6 ; i++){
		vec3 t =  _p - p[i].v[0];
		float v = (t * p[i].normalAt(_p));
		if (   (v < EPSILON/2.0f) && (v > -EPSILON/2.0f)){
			face = i;
			if (i != 0)
			{
				int bbb = 3;
			}
			return p[i].normalAt(_p);
		}
	}
	face = -1;
	return vec3(0,0,0);
}

void Box::fill(){
	if (!filled){
		
		const int B = 0;
		const int T = 5;

		p[1].v[0] = p[B].v[0];
		p[1].v[1] = p[B].v[2];
		p[1].v[2] = p[T].v[0];
		

		p[2].v[0] = p[B].v[2];
		p[2].v[1] = (p[B].v[1] - p[B].v[0]) + (p[B].v[2] - p[B].v[0]) + p[B].v[0];
		p[2].v[2] =  p[T].v[1];
		
		p[3].v[0] = (p[B].v[1] - p[B].v[0]) + (p[B].v[2] - p[B].v[0]) + p[B].v[0];
		p[3].v[1] = p[B].v[1];
		p[3].v[2] = (p[T].v[1] - p[T].v[0]) + (p[T].v[2] - p[T].v[0]) + p[T].v[0];
		

		p[4].v[0] = p[B].v[1];
		p[4].v[1] = p[B].v[0];
		p[4].v[2] = p[T].v[2];
		

		
		filled = true;
	}
}

float Box::getArea(){
	float area = 0;
	for (size_t i = 0; i < 6; i++){
		area+= p[i].Area();
	}
	return area;
}


void Box::print(ostream& out) const{
	out<< "box: " << std::endl;
	for (size_t i = 0 ; i < 6; i++){
		out << "\t\t" <<i << ": "<< p[i] << std::endl;
	} 
	out << *material ;
}

ostream& operator<<(ostream& os,const Box& s){
	s.print(os);
	return os;
}

#endif 
