// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:triangle.cpp
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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "triangle.h"



float Triangle::intersects(const ray& r)  {
	vec3 U = v[1] - v[0]; 
	vec3 V = v[2] - v[0];
	vec3 N = normalAt(r.pos);

	if ( (N.x == 0) && (N.y == 0) && (N.z == 0) ) //triangle degenerate
		return NO_INTERSECTION;
	vec3 w0 = r.pos - v[0];
	float a = - (N * w0);
	float b = (N * r.direction);

	if (fabs(b) < EPSILON) { //small number floating precision :(
		// if (a == 0 ) ray and triangle same plane
		// else disjoint from plane
		return NO_INTERSECTION;
	}

	float rt = a/b;
	if (rt < EPSILON)
		return NO_INTERSECTION;  // not in in their direction.
	vec3 P = r.pos + rt*r.direction;

	// Inside triangle
	float    uu, uv, vv, wu, wv, D;
    uu = U * U;
    uv = U * V;
    vv = V * V;
    vec3 W = P - v[0];
    wu = W * U;
    wv = W * V;
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)        // I is outside T
        return NO_INTERSECTION;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
		return NO_INTERSECTION;

    return rt;                      // I is in T
}
vec3 Triangle::getLightPoint(){
	float u = urandom(), _v = (1 - u) * urandom();
	vec3 U = v[1] - v[0]; 
	vec3 V = v[2] - v[0];
	return v[0] + u*U + _v*V;
}
vec3  Triangle::normalAt(const vec3& p)  {
	return (v[1]-v[0]).cross(v[2]-v[0]).normalize();
}

float Triangle::getArea(){
		vec3 U = v[1] - v[0]; 
		vec3 V = v[2] - v[0];

		vec3 U1 = U.normalize();
		vec3 V1 = U.normalize();
		float cos = U1 * V1;
		float sin = sqrtf(1.0f - cos*cos); 
		float u = U.length();
		float v = V.length();

		return u*v*sin/2.0f;
}

void Triangle::print(ostream& out) const{
	out<< "triangle: " ;
	for (size_t i = 0 ; i < 3; i++){
		out << "v" << (i+1) << "(" << v[i].x <<","<< v[i].y <<"," << v[i].z << ") ";
	} 
	out << *material ;
}
ostream& operator<<(ostream& os,const Triangle& s){
	s.print(os);
	return os;
}

#endif
