// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:configreader.h
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

#ifndef CONFIG_H
#define CONFIG_H


#include <string>
#include <fstream>
#include "vec3.h"
#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "disc.h"
#include "triangle.h"
#include "frame.h"
#include "box.h"
#include "camera.h"


using std::string;
using std::ifstream;


class ConfigReader{	
	ifstream is_f;
	Scene _s;
	public:
		ConfigReader(const string& fileName);
		Scene* parse();
		~ConfigReader();
	protected:

		  void parseObject( string in, string& label, string& rest );
		  void getLabel( string in, string& label, string& rest ); 
		  void getValue( string in, string& value, string& rest );

		  bool readVector(string& value, vec3& v);
		  bool readTuple(string& value, vec2& v);
		  bool readValue(string&  value, float& v);

		  bool parseMaterial(string& in, Material& m);
		  bool parseScene(string& in, Scene& s);
		  bool parseSphere(string& in, Sphere& s);
		  bool parsePlane(string& in, Plane&  p);
		  bool parseDisc(string& in, Disc&  c);
		  bool parseTriangle(string& in, Triangle& t);
		  bool parseFrame(string& in, Frame& f);
		  bool parseBox(string& in, Box& b);
		  bool parseCamera(string& in, Camera& c);

		  bool getMaterial(string& label,string& svalue, Object& m,string t="material");
};


#endif



