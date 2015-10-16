// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:scene.h
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

#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include <vector>
#include "camera.h"

using std::string;
using std::vector;


class Scene {
	public:
		vector<Object*>  objects;
		vector<Object*>  olights;

		vector<Material*> materials;
		Camera camera;

		int antialising;
		float exposure;
		bool direct;
		bool indirect;
		size_t iter;
		size_t spp;        //samples per pixel
		vec3   background; //background color

		Scene(): camera(),
				 antialising(false),
				 exposure(-3.0f),
				 direct(true),
				 indirect(true),
				 iter(10),
				 spp(10){};
		~Scene();

		void render(string filename);
		
		
	private:
		vec3 radiance(ray& r,int depth, int E );
		int  closest_object(ray r,float& t);
};

ostream& operator<<(ostream& os,const Scene& s);



#endif
