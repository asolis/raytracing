// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:disc.cpp
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

#ifndef DISC_CPP
#define DISC_CPP


#include "disc.h"

float Disc::intersects(const ray& r)  {

	vec3 N = normal;
	     N = N.normalize();

    float d = - ( N * center);
	float t = - ((r.pos*N )+d);
	float td= N * r.direction;

	if (td > 0.0 ) return NO_INTERSECTION;
	
	t *= (1.0f/td);

	if (t < EPSILON ) return NO_INTERSECTION;

	vec3 l = r.pos + t * r.direction;
	vec3 c = center;
	if (c.distanceSq(l) > (radius*radius)) return NO_INTERSECTION;
	return t;
}
vec3 Disc::getLightPoint()
{
	ONB onb = ONB::initFromW(normal);

	float u = urandom()*2.0f -1.0f;
	float v = urandom()*2.0f -1.0f;

	while ( sqrt((u)*(u) + (v)*(v)) > 1) {
		u = urandom()*2.0f -1.0f;
		v = urandom()*2.0f -1.0f;
	}

	vec3 lp = onb.getVecInONB( (u*radius), (v*radius),0);
	return lp + center;
}
vec3  Disc::normalAt(const vec3& p)  {
	vec3 N = normal;

	return N.normalize();
}

float Disc::getArea(){
	return 2.0f*M_PI*radius*radius;
}
void Disc::print(ostream& out) const{
	out<< "disc: " 
	<< "c("           << center.x << "," 
					  << center.y << ","				          
					  << center.z << ") " 
	<< "n("           << normal.x << "," 
					  << normal.y << ","				          
					  << normal.z << ") " 
	<< "radius("      << radius << ") "
	<< *material;
}
ostream& operator<<(ostream& os,const Disc& s){
	s.print(os);
	return os;
}


#endif
