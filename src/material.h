// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:material.h
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

#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include <cmath>
#include "vec3.h"
#include "onb.h"

using namespace std;

static float urandom(){
	return  float(rand())/float(RAND_MAX);
}

enum MType { DIFF, SPEC, REFR, SPECP, DSPEC };

class Material { 
	
public:

		vec3 e,c,d,s;  // emission,color, diffuse, specular

		float n;     // power

		MType type;
		float rIndex;

		Material(): d(0,0,0),
					s(0,0,0),
					e(0,0,0),
					c(0,0,0),
					n(0),
					rIndex(0),
					type(DIFF){}
		
		virtual bool emits() { 
			return ( e.x + e.y + e.z )> 0 ;
		}
	
		virtual bool brdf(vec3& N, vec3& V, vec3& L, vec3& brdf){
			return false;
		}
		virtual bool outDirection(const vec3& N,       //normal
								  const vec3& V,		 //Viewer - Eye
								  vec3& rgb,	 //Color of material
								  vec3& out,	 //outgoing ray direction
								  float& f_scale)//fresnel_scale  NOTE: only ussed in Transmissive Materials
		{
			return false;
		}	
		virtual Material* clone() {
			return new Material(*this);
		}
		virtual float maxRadiance(){
			return std::max(c.x,std::max(c.y,c.z));
		}
		virtual vec3 Radiance(){
			return c;
		}
};

inline ostream& operator<<(ostream& os,const Material& m){
	os  << "material: " ;
	if (m.e.x + m.e.y + m.e.z > 0 )
		os << "l(yes) e(" << m.e.x << "," << m.e.y <<"," << m.e.y << ") ";
	if (m.c.x + m.c.y + m.e.z > 0 )
		os << "c("   << m.c.x << "," << m.c.y << "," << m.c.z << ") ";
	if (m.d.x + m.d.y + m.d.z > 0 )
		os << "d("   << m.d.x << "," << m.d.y << "," << m.d.z << ") ";
	if (m.s.x + m.s.y + m.s.z > 0 )
		os << "s("  << m.s.x<< "," << m.s.y<< "," << m.s.z<< ") ";
	if (m.n > 0) 
		os << "p(" << m.n   << ") ";
	if (m.type == REFR)
		os << "ri(" << m.rIndex << ") ";
	return os;
}

class DiffuseMaterial: public Material{
	
		public:
			
		DiffuseMaterial(const Material& m): Material(m){}
		bool brdf(vec3& N, vec3& V, vec3& L, vec3& brdf){
			brdf = d.scalar_mult(c);	
			return true;
		}
		bool outDirection(const vec3& N,const vec3& V, vec3& rgb, vec3& out,float& f_scale){
			float u  = urandom();
			float v  = urandom();
			//float w1 = cos(2.0f*M_PI*u)*sqrtf(v), w2 = sin(2.0f*M_PI*u)*sqrtf(v), w3 = sqrtf(1.0f-v);
			float w1 = cos(2.0f*M_PI*u)*sqrtf(v), w2 = sin(2.0f*M_PI*u)*sqrtf(v), w3 = sqrtf(1.0f-(w1*w1)-(w2*w2));
			ONB onb  = ONB::initFromW(N);
				out  = onb.getVecInONB(w1,w2,w3).normalize();
			f_scale  = 1.0f;
			return true;
		}
		virtual Material* clone() {
			return new DiffuseMaterial(*this);
		}
};


class MirrorMaterial: public Material{
	public:
		MirrorMaterial(const Material& m): Material(m){}
		
	
		bool outDirection(const vec3& N,const vec3& V, vec3& rgb, vec3& out,float& f_scale){
			float cosNV  = N * V;
			rgb   = rgb + (1.0f - rgb) * powf((1.0f-abs(cosNV)),5.0f);
			out = V +  (-2.0f *cosNV * N);
			f_scale  = 1.0f;
			return (out*N) > 0;
		}
		virtual Material* clone() {
			return new MirrorMaterial(*this);
		}
		
};


class PhongMetalMaterial: public Material{
		
	public:
		PhongMetalMaterial(const Material& m): Material(m){}
		
		bool brdf(vec3& N, vec3& V, vec3& L, vec3& brdf){
						//specular term
			vec3 H   = (L + (-1.0 *V)).normalize();
			brdf = (  s * pow(N*H, n) )  ;	
			return true;
		}
		
		bool outDirection(const vec3& N,const vec3& V, vec3& rgb, vec3& out,float& f_scale){
			float cosNV  = N * V;
			rgb = rgb + (1.0f - rgb) * pow((1.0f-abs(cosNV)),5.0f);
			float u = urandom();
			float v = urandom();
			vec3  sdir = (V + (-2.0f * cosNV * N)).normalize();
			float phi = 2.0f * M_PI * u;
			float exp = n; 
			float cosTheta = pow(1.0f - v, 1.0f/(exp+1));
			float sinTheta = (1.0f - cosTheta*cosTheta);
			ONB onb = ONB::initFromW(sdir);
			float w1 = cos(phi) * sinTheta, w2 = sin(phi) * sinTheta, w3 =  cosTheta;
			out = onb.getVecInONB(w1,w2,w3).normalize();
			f_scale = 1.0f;
			return (sdir*N) > 0;
		}
		virtual Material* clone() {
			return new PhongMetalMaterial(*this);
		}
		
};


class DiffSpecularMaterial: public Material{
	
		public:
		DiffSpecularMaterial(const Material& m): Material(m){}
		bool brdf(vec3& N, vec3& V, vec3& L, vec3& brdf){
						//specular term
			vec3 H   = (L + (-1.0 *V)).normalize();
			brdf = ( d+ s * pow(N*H, n) )  ;	
			return true;
		}

		bool outDirection(const vec3& N,const vec3& V, vec3& rgb, vec3& out,float& f_scale){
			float cosine = abs(N * V);
			float cosNV  = N * V;
			float temp1  = 1.0f - cosine;
				  rgb = rgb + (1.0f -rgb) * pow(temp1,5.0f);
			float maxR = std::max(rgb.x,std::max(rgb.y,rgb.z));
			float P = (maxR + 0.5f)/ 2.0f ;
			f_scale = 1.0f;
			if (urandom() <= P) {
				out = (V + (-2.0f * cosNV * N)).normalize();
				rgb = rgb/P;				
			} else {
				float u = urandom();
				float v = urandom();
				rgb = (1.0f - rgb)/(1.0f-P);
				rgb = rgb.scalar_mult(d);
				//float w1 = cos(2.0f*M_PI*u)*sqrtf(v), w2 = sin(2.0f*M_PI*u)*sqrtf(v), w3 = sqrtf(1.0f-v);
				float w1 = cos(2.0f*M_PI*u)*sqrtf(v), w2 = sin(2.0f*M_PI*u)*sqrtf(v), w3 = sqrtf(1.0f-(w1*w1)-(w2*w2));
				ONB onb = ONB::initFromW(N);
					out  = onb.getVecInONB(w1,w2,w3).normalize();
				
			}
			return true;
		}
		virtual Material* clone() {
			return new DiffSpecularMaterial(*this);
		}
};


class DielectricMaterial: public Material{
	public:
		DielectricMaterial(const Material& m): Material(m){}
	
		bool outDirection(const vec3& N,const vec3& V, vec3& rgb, vec3& out,float& f_scale){
			     // Ideal dielectric REFRACTION
			vec3 NL= ( N * V <0 )? N : -1.0f * N ;
			//rgb   = c;
			bool into = (N * NL ) > 0;                // Ray from outside going in?
			float nc=1.0f; 
			float nt=rIndex;
			float nnt=into?nc/nt:nt/nc;
			float ddn=V * NL;
			float cos2t=1.0f-nnt*nnt*(1.0f-ddn*ddn);
			if (cos2t<0) {   // Total internal reflection
				out =  V - N*2.0f*(N * V);
				f_scale = 1.0f;
				return true;
			}
			vec3 tdir = (V*nnt - N*((into?1.0f:-1.0f)*(ddn*nnt+sqrtf(cos2t)))).normalize();
			float a=nt-nc;
			float b=nt+nc;
			float R0=a*a/(b*b);
			float c = 1.0f-(into?-ddn:tdir * N);
		    float Re=R0+(1.0f-R0)*pow(c,5.0f);
			float Tr=1.0f-Re;
			float P=.25f+.5f*Re;
			float RP=Re/P;
			float TP=Tr/(1.0f-P);

			
			if (urandom() < P) {
				f_scale = RP;
				out =  V - N*2.0f*(N * V);
			}else {
				f_scale = TP;
				out = tdir;
			}

			return true;
		}

		virtual Material* clone() {
			return new DielectricMaterial(*this);
		}
		
};


#endif
