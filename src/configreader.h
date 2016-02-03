// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:configreader.h
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



