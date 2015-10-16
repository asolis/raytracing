// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:vec3.h
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

