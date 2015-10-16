// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:vec3.cpp
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

#ifndef VEC3_CPP
#define VEC3_CPP


#include <cmath>
#include "vec3.h"


using namespace std;

vec3 vec3::normalize() const{
	float  _sqr = sqrtf	(x*x + y*y + z*z);
	if (_sqr == 0) 
		return vec3(0,0,0);
	_sqr = 1.0f/_sqr;

	return  vec3(x * _sqr, y * _sqr, z * _sqr );
}

vec3 vec3::scalar_mult(const vec3& v){
		
	return vec3(x*v.x,y*v.y,z*v.z);
}

vec3& vec3::operator+=(const vec3& v){
	this->x +=v.x;
	this->y +=v.y;
	this->z +=v.z;
	return *this;
}

float& vec3::operator[] (const size_t i){
	switch(i){
		case 0:
			return x;
		case 1:
			return y;
		default:
			return z;
	}
}
vec3 vec3::cross(const vec3& v){
	return vec3((y*v.z) - (z*v.y),
				(z*v.x) - (x*v.z),
				(x*v.y) - (y*v.x));
}

float vec3::norm(){
	return length();
}
float vec3::distanceSq(vec3& v){
	return powf(x-v.x,2.0f)+powf(y-v.y,2.0f)+powf(z-v.z,2.0f);
}

float vec3::length(){
	return sqrtf(x*x + y*y + z*z);
}


 ostream& operator<<(ostream& os, const vec3& v){
	os << v.x << ", " << v.y <<", " << v.z ;
	return os;
}

 vec3 operator+ (const vec3& v1, const vec3& v2){
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
 vec3 operator+ (const vec3& v1, const float& v){
	return vec3(v1.x + v, v1.y + v, v1.z + v);
}
 vec3 operator- (const vec3& v1, const vec3& v2){
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
 vec3 operator- (const vec3& v1, const float v2){
	return vec3(v1.x - v2, v1.y - v2, v1.z - v2);
}
 vec3 operator- (const float v2, const vec3& v1 ){
	return vec3(v2 - v1.x ,v2 - v1.y ,v2 - v1.z );
}
 vec3 operator* (const float v, const vec3& v2){
	return vec3(v2.x*v,v2.y*v,v2.z*v);
}
 vec3 operator* ( const vec3& v2,const float v){
	return vec3(v2.x*v,v2.y*v,v2.z*v);
}
 float operator* ( const vec3& v1,const vec3& v2){
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
 vec3 operator/ ( const vec3& v2,const float v){
	return vec3(v2.x/v,v2.y/v,v2.z/v);
}


#endif
