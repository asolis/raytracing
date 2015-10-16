// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:box.cpp
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
