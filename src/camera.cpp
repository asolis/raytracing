// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:camera.cpp
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

#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.h"
using std::endl;


ray Camera::getRay(float x, float y){
	ray r;

	vec3 w   = -1.0f * direction.normalize();
	vec3 v   = up.normalize();
	vec3 u   = w.cross(v);

	float cu = x - .5f*resolution.x;
	float cv = y - .5f*resolution.y;

	vec3 Pij = center + cu * u  + cv * v;

	if (flength == 0) {
		r.pos = Pij;
		r.direction = -1.0*w;
		return r;
		
	}

	vec3 E   = center + flength * w;
	

	r.pos = E;
	r.direction = (Pij - E).normalize();
	return r;
}


ostream& operator<<(ostream& os,const Camera& s){
	os  << "camera:  " << endl
		<< "\tcenter("         << s.center.x  << ","
						<< s.center.y  << ","
						<< s.center.z  << ") " ;
	os	<< "\tup("        << s.up.x  << ","
						<< s.up.y  << ","
						<< s.up.z  << ") " ;
	os	<< "\tdir("       << s.direction.x  << ","
						<< s.direction.y  << ","
						<< s.direction.z  << ") " <<endl; 
	os	<< "\tresolution("       << s.resolution.x  << ","
						       << s.resolution.y  << ") " ; 
	os	<< "\tflength("   << s.flength  << ") ";
	return os;
}

#endif 
