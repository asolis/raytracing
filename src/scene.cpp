// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:scene.cpp
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

#ifndef SCENE_CPP
#define SCENE_CPP

#include <iostream>
#include <limits>
#include <math.h>
#include "scene.h"
#include "otgastream.h"
#include "onb.h"



int Scene::closest_object(ray view, float &t){
	int object = -1;
	for (size_t i = 0; i < objects.size(); i++){
		float _t = objects[i]->intersects(view);
		if ((_t < t) && (_t > abs(EPSILON))) {
			t = _t;
			object = i;
		}
	}
	return object;
}



vec3 Scene::radiance(ray& view,int depth, int CEL=1){
	
		
		// Distance(t) and index of the closest object
		float t  = std::numeric_limits<float>::max();
		int index = closest_object(view,t);


		//radiance is increasing! this might be possible if initial radiance values
		//are >=1 or to close to 1. 
		if (depth >= 500) return background;
		
		// If no intersection return background color
		if  (index == NO_INTERSECTION) 
			return background; 
		
		// Intersection point
		vec3 hit = view.pos +  view.direction * t;
		// Normal at itersection point
		vec3 N   = objects[index]->normalAt(hit);
				
		// Material of the object hit
		Material *m = objects[index]->getMaterial();

	
		vec3  R     = m->Radiance();
		
		float cosVN = view.direction * N;
		//if (cosVN > 0 ) return background;
		float p     = m->maxRadiance();
			  p     = (p >= 1.0f)? p-EPSILON : p ;



		if ( (unsigned)depth > iter || !p) {
			if ( urandom() < p) 
				R = R*1.0f/p;
			else 
				return m->e*float(CEL);
		}

		vec3 e(0,0,0);
		//compute direct illumination
		if (direct && (m->type==DIFF || m->type == DSPEC)){
		for (size_t i = 0; i < olights.size(); i++){				

			    vec3 _x     = olights[i]->getLightPoint();
				vec3 L		= (_x - hit).normalize();
				//move a little bit foward to advoid precision errors
				ray s(hit+(EPSILON*L),L); 

				float tL = std::numeric_limits<float>::max();
				int index2 = closest_object(s,tL);

				if ( (index2 != -1 ) && ( objects[index2]->isLight())) {
					//need to check if it's the same light source

					vec3 LN     = olights[i]->normalAt(_x);
					float theta = N * L;
						  theta = (theta<0)?0:theta;
					vec3  d      = (_x - hit);
					float d2     = d*d;
					float Ltheta = (-1.0f * L)*LN;
						  Ltheta = (Ltheta<0)?0:Ltheta;
					float area   = olights[i]->Area();


					vec3 brdf;
					m->brdf(N,view.direction,L,brdf);

					vec3 le = olights[i]->getMaterial()->e;
					e += R.scalar_mult(le * theta * Ltheta ).scalar_mult(brdf)*area/d2; 
				}
				e = e * 1.0f/(float)olights.size();
				
		}
			CEL = 0;
			
		}

		//If the previous surface sent a shadow ray ,the segment does not emits light
		//Shirley's book.  All the specular surfaces here don't sent a shadow light;
		CEL = (m->type != DIFF)? 1: CEL;

		if (indirect) {
			vec3 out; 
			float fs;
			if (m->outDirection(N,view.direction,R,out,fs)){
				ray _oray(hit + (EPSILON)*out,out);
				
				return m->e *float(CEL) + e + R.scalar_mult(fs*radiance(_oray,depth+1,CEL));
			}
		} 
	
		return m->e*float(CEL)+e;

}

void Scene::render(string filename){

	int WIDTH = (int)camera.resolution.x;
	int HEIGHT= (int)camera.resolution.y;
	otgastream image(filename,WIDTH,HEIGHT);

	int *output = new int[WIDTH*HEIGHT];

	for (int y = 0; y < HEIGHT; y++) {
		#pragma omp parallel for schedule(dynamic, 1) 
		for (int x = 0; x < WIDTH; x++) {	
		
	
			vec3 r(0,0,0);
		
			if (antialising){
				//pretty simple approach of super - sampling. x^2 
				float step = 1.0f/antialising;
				float weight = 1.0f/(antialising * antialising);
				for (float fx = float(x) ; fx < x + 1.0f; fx += step )
				for (float fy = float(y) ; fy < y + 1.0f; fy += step )
				{
					vec3 temp;
				
					for(size_t s = 0; s < spp; s++){
						ray view = camera.getRay(fx,fy);
							temp += radiance(view,0,1) * (1.0f/float(spp));
					}
					if (exposure != 0) {
						temp.x = (1.0f - expf(temp.x * exposure));
						temp.y = (1.0f - expf(temp.y * exposure));
						temp.z = (1.0f - expf(temp.z * exposure));
					}
					r += weight * temp;
				}

			} else {

				
				
					for(size_t s = 0; s < spp; s++){
						ray view = camera.getRay((float)(x+0.5f),(float)(y+0.5f));
							r += radiance(view,0,1) * (1.0f/float(spp));
					}
					if (exposure != 0){
						r.x = (1.0f - expf(r.x * exposure));
						r.y = (1.0f - expf(r.y * exposure));
						r.z = (1.0f - expf(r.z * exposure));
					}
			}
		
			size_t pos = y*WIDTH+x;
			output[pos] =        ((unsigned char) std::min(r.x*255.0,255.0) << 16 |
								  (unsigned char) std::min(r.y*255.0,255.0) << 8  |
								  (unsigned char) std::min(r.z*255.0,255.0));
		}
	

		int percentage = (int) (100.0f *  float( y )/(float( HEIGHT)-1.0f));
		printf("%.3d %% \r", percentage);

	}

	for (size_t i = 0; i < size_t(WIDTH*HEIGHT) ; i++){
		image.putInt(output[i]);
	}
	delete[] output;

	image.flush();
	image.close();
	
}

Scene::~Scene(){	
	vector<Object*>::iterator i = objects.begin();
	for (; i != objects.end(); i++)
	{
		delete *i;
	}

	vector<Material*>::iterator m = materials.begin();
	for (; m != materials.end(); m++)
	{
		delete *m;
	}
}

ostream& operator<<(ostream& os,const Scene& s){
	os  << "scene:  " <<endl;
	os  << "\tantialiasing: "   << s.antialising << endl;
	os  << "\texposure: " << s.exposure << endl;
	os  << "\tmin bounces: "   << s.iter << "\tspp: " << s.spp <<
		   "\tbackground: rgb(" << s.background.x << "," <<
								   s.background.y << "," <<
								   s.background.z << ") "<< endl << endl;
	os << "\tDirect Illumination:   " << (  (s.direct)?"yes":"no") <<endl;
	os << "\tIndirect Illumination: " << ((s.indirect)?"yes":"no") <<endl <<endl; 
	
	os  << s.camera << endl;
	
	os  << endl << "materials:" << endl;
	for (size_t i = 0; i < s.materials.size(); i ++){
		os << "\t" << i+1 << " ] " << *s.materials[i] << endl;
	}
	os  << endl << "objects:" << endl;
	for (size_t i = 0; i < s.objects.size(); i ++){
		os << "\t"  << i+1 << " ] " << *(s.objects[i]) << endl;
	}
	return os;
}

#endif
