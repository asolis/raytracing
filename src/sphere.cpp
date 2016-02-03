// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:sphere.cpp
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

#ifndef SPHERE_CPP
#define SHPERE_CPP

#include "sphere.h"
#include <cmath>


float Sphere::intersects(const ray& r)  {

	vec3 dist = center - r.pos; 
	float B = r.direction * dist;
    
    float D = B*B - dist * dist + radius * radius; 
    if (D < 0.0) 
        return NO_INTERSECTION; 
    float t0 = B - sqrt(D); 
    float t1 = B + sqrt(D);

	float rs = NO_INTERSECTION; 
	if (t0 >= EPSILON ){
		rs = t0;
	}
	if (t1 >= EPSILON){
		if (rs == NO_INTERSECTION) rs = t1;
		else 
			rs = std::min(rs,t1);
	}
	

	return rs;
}

vec3 Sphere::getLightPoint(){
	float x,y,z,t;
	z = ( urandom() * 2 ) - 1;  //random uniform between -1, 1
	t = ( urandom() * 2 * M_PI); //random uniform between 0, 2pi

	x= sqrtf(1.0f - (z*z)) * cos(t);
	y= sqrtf(1.0f - (z*z)) * sin(t);

	vec3 p =  vec3(x,y,z)*radius + center;
	return p;
}


vec3  Sphere::normalAt(const vec3& p)  {
	return (p-center).normalize();
}
float Sphere::getArea(){
	return 4.0f*M_PI*radius*radius;
}


void Sphere::print(ostream& out) const{
	out<< "sphere: " 
	<< "c("           << center.x << "," 
					  << center.y << ","				          
					  << center.z << ") " 
	<< "r("           << radius << ") " 
	<< *material ;
}
ostream& operator<<(ostream& os,const Sphere& s){
	s.print(os);
	return os;
}

#endif 
