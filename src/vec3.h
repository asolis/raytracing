// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:vec3.h
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

#ifndef VEC3_H
#define VEC3_H


#ifndef M_PI
#define M_PI 3.14159f
#endif 

#ifndef EPSILON
#define EPSILON  0.005f
#endif

#ifndef NO_INTERSECTION
#define NO_INTERSECTION  -1.0f
#endif

#include <ostream>

using std::ostream;


struct vec2{
	float x;
	float y;
	vec2(const float _x = 0, 
		 const float _y = 0) : x(_x), y(_y){}
	
};


struct vec3{

	float x;
	float y;
	float z;

	vec3(const float _x = 0,
		 const float _y = 0,
		 const float _z = 0): x(_x), y(_y), z(_z){}

	vec3&	 operator+=(const vec3& v);
	float&	 operator[] (const size_t i);

	vec3 normalize() const;
	vec3 scalar_mult(const vec3& v);
	vec3 cross(const vec3& v);
	float norm();
	float distanceSq(vec3& v);
	float length();
};

 ostream&	operator<<(ostream& os, const vec3& v);
 vec3		operator+ (const vec3& v1, const vec3& v2);
 vec3		operator+ (const vec3& v1, const float& v);
 vec3		operator- (const vec3& v1, const vec3& v2);
 vec3		operator- (const vec3& v1, const float v2);
 vec3		operator- (const float v2, const vec3& v1 );
 vec3		operator* (const float v, const vec3& v2);
 vec3		operator* ( const vec3& v2,const float v);
 float		operator* ( const vec3& v1,const vec3& v2);
 vec3		operator/ ( const vec3& v2,const float v);

struct ray{
	vec3 pos;
	vec3 direction;
	ray(vec3 p, vec3 d): pos(p),direction(d){}
	ray():pos(0,0,0),direction(0,0,0){}
};

 
#endif 

