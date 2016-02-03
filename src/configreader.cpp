// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:configreader.cpp
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
#ifndef CONFIG_CPP
#define CONFIG_CPP


#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "configreader.h"

using namespace std;

ConfigReader::ConfigReader(const string& fileName): is_f(fileName.c_str()), _s() {
	if(!is_f) throw string("File not found: " )+= fileName;
}
ConfigReader::~ConfigReader() {
  if (is_f) is_f.close();
}
Scene* ConfigReader::parse(){
	
	string line, label, rest, svalue;
	while ( getline(is_f,line)){
		    parseObject(line,label,rest);

			if (label == "sphere"   )  {
				Sphere* s = new Sphere();
				if (parseSphere(rest,*s)){
					_s.objects.push_back(s);
					
				}
				if (s->isLight())
					_s.olights.push_back(s);
			}
			else if (label == "scene"    )  {
				if (parseScene(rest,_s)){
					
				}
			}
			else if (label == "camera"    )  {
				
				if (parseCamera(rest,_s.camera)){
					
				}
			}else if (label == "material" )  {
				Material tmp;
				Material *m = NULL;
				if (parseMaterial(rest,tmp)){
					switch (tmp.type) {
					case DIFF:
						m = new DiffuseMaterial(tmp);
						break;
					case SPEC:
						m = new MirrorMaterial(tmp);
						break;
					case SPECP:
						m = new PhongMetalMaterial(tmp);
						break;
					case DSPEC:
						m = new DiffSpecularMaterial(tmp);
						break;
					case REFR:
						m = new DielectricMaterial(tmp);
						break;
					}
					_s.materials.push_back(m);
				}
			}
			else if (label == "plane"    )  {
				Plane* p  = new Plane();
				if (parsePlane(rest,*p)){
					_s.objects.push_back(p);
					
				}
				if (p->isLight())
					_s.olights.push_back(p);
			}
			else if (label == "frame"    )  {
				Frame* f  = new Frame();
				if (parseFrame(rest,*f)){
					_s.objects.push_back(f);
					
				}
				if (f->isLight())
					_s.olights.push_back(f);
			}
			else if (label == "disc"    )  {
				Disc* c  = new Disc();
				if (parseDisc(rest,*c)){
					_s.objects.push_back(c);
					
				}
				if (c->isLight())
					_s.olights.push_back(c);
			}
			if (label == "triangle"    )  {
				Triangle* t  = new Triangle();
				if (parseTriangle(rest,*t)){
					_s.objects.push_back(t);
					
				}
				if (t->isLight())
					_s.olights.push_back(t);
			}
			else if (label == "box"     )  {
				Box* b  = new Box();
				if (parseBox(rest,*b)){
					b->fill();
					_s.objects.push_back(b);
					
				}				
				if (b->isLight())
					_s.olights.push_back(b);
			}			
	}
	
	return &_s;
}
bool ConfigReader::parseCamera(string& in, Camera& c){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "center") {
						
						if (!readVector(svalue,c.center)) {
							std::cerr << "Problem reading Camera center { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "up") {
						
						if (!readVector(svalue,c.up)) {
							std::cerr << "Problem reading Camera up vector { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "resolution") {
						
						if (!readTuple(svalue,c.resolution)) {
							std::cerr << "Problem reading screen resolution { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "direction") {
						
						if (!readVector(svalue,c.direction)) {
							std::cerr << "Problem reading Camera direction { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "flength") {
						
						if (!readValue(svalue,c.flength)) {
							std::cerr << "Problem reading Camera focal length { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					
	}
	return true;
}
bool ConfigReader::parseBox(string& in, Box& b){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "b1") {
						
						if (!readVector(svalue,b.p[0].v[0])) {
							std::cerr << "Problem reading Box Bottom v1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "b2") {
						
						if (!readVector(svalue,b.p[0].v[1])) {
							std::cerr << "Problem reading Box Bottom v1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "b3") {
						
						if (!readVector(svalue,b.p[0].v[2])) {
							std::cerr << "Problem reading Box Bottom v3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "t1") {
						
						if (!readVector(svalue,b.p[5].v[0])) {
							std::cerr << "Problem reading Box Top v1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "t2") {
						
						if (!readVector(svalue,b.p[5].v[1])) {
							std::cerr << "Problem reading Box Top v2 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}		
					else if (label == "t3") {
						
						if (!readVector(svalue,b.p[5].v[2])) {
							std::cerr << "Problem reading Box Top v3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}		
					/*else if (!getMaterial(label,svalue,*b.p[0].material,"matb"))
					{
						std::cerr << "Problem reading Box material B { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
					else if (!getMaterial(label,svalue,*b.p[1].material,"mat1"))
					{
						std::cerr << "Problem reading Box material 1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
					else if (!getMaterial(label,svalue,*b.p[2].material,"mat2"))
					{
						std::cerr << "Problem reading Box material 2 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
					else if (!getMaterial(label,svalue,*b.p[3].material,"mat3"))
					{
						std::cerr << "Problem reading Box material 3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
					else if (!getMaterial(label,svalue,*b.p[4].material,"mat4"))
					{
						std::cerr << "Problem reading Box material 4 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
					else if (!getMaterial(label,svalue,*b.p[5].material,"matt:"))
					{
						std::cerr << "Problem reading Box material T { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}*/
					else  if (label== "material"){
						if (!getMaterial(label,svalue,b)){
							std::cerr << "Problem reading Box material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						} 
						for (size_t i = 0; i < 6 ; i ++)
						{
							b.p[i].material = b.material;
						}
					}
	}
	return true;
}
bool ConfigReader::parseFrame(string& in, Frame& f){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "v1") {
						
						if (!readVector(svalue,f.v[0])) {
							std::cerr << "Problem reading Frame v1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "v2") {
						
						if (!readVector(svalue,f.v[1])) {
							std::cerr << "Problem reading Frame v2 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "v3") {
						
						if (!readVector(svalue,f.v[2])) {
							std::cerr << "Problem reading Frame v3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "h1") {
						
						if (!readTuple(svalue,f.h[0])) {
							std::cerr << "Problem reading Frame h1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "h2") {
						
						if (!readTuple(svalue,f.h[1])) {
							std::cerr << "Problem reading Frame h2 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "h3") {
						
						if (!readTuple(svalue,f.h[2])) {
							std::cerr << "Problem reading Frame h3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (!getMaterial(label,svalue,f)){
							std::cerr << "Problem reading Circle material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
	}
	return true;
}
bool ConfigReader::parsePlane(string& in, Plane& p){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "v1") {
						
						if (!readVector(svalue,p.v[0])) {
							std::cerr << "Problem reading Plane v1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "v2") {
						
						if (!readVector(svalue,p.v[1])) {
							std::cerr << "Problem reading Plane v2 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "v3") {
						
						if (!readVector(svalue,p.v[2])) {
							std::cerr << "Problem reading Plane v3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (!getMaterial(label,svalue,p)){
							std::cerr << "Problem reading Circle material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
	}
	return true;
}
bool ConfigReader::parseDisc(string& in, Disc& c){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "center") {
						
						if (!readVector(svalue,c.center)) {
							std::cerr << "Problem reading Disc Center { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "radius") {
						
						if (!readValue(svalue,c.radius)) {
							std::cerr << "Problem reading Disc radius { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "normal") {
						
						if (!readVector(svalue,c.normal)) {
							std::cerr << "Problem reading Disc normal { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						c.normal = c.normal.normalize();
						
					}
					else if (!getMaterial(label,svalue,c)){
							std::cerr << "Problem reading Disc material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
	}
	return true;
}
bool ConfigReader::parseTriangle(string& in, Triangle& t){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "v1") {
						
						if (!readVector(svalue,t.v[0])) {
							std::cerr << "Problem reading Triangle v1 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "v2") {
						
						if (!readVector(svalue,t.v[1])) {
							std::cerr << "Problem reading Triangle v2 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "v3") {
						
						if (!readVector(svalue,t.v[2])) {
							std::cerr << "Problem reading Triangle v3 { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (!getMaterial(label,svalue,t)){
							std::cerr << "Problem reading Circle material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
	}
	return true;
}
bool ConfigReader::parseSphere(string& in, Sphere& s){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "center") {
						
						if (!readVector(svalue,s.center)) {
							std::cerr << "Problem reading Sphere center { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label == "radius") {
						
						if (!readValue(svalue,s.radius)) {
							std::cerr << "Problem reading Sphere radius { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else  if (!getMaterial(label,svalue,s)){
							std::cerr << "Problem reading Sphere material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
					}
					

	}
	return true;
}
bool ConfigReader::parseScene(string&in , Scene& s){
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					if (label == "background") {
						
						if (!readVector(svalue,s.background)) {
							std::cerr << "Problem reading Scene spl { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					} 
					else  if (label == "spp") {
						
						float v;
						if (!readValue(svalue,v)) {
							std::cerr << "Problem reading Scene spp { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						s.spp = (int)v;
						
					} 
					else  if (label == "exposure") {
						
						
						if (!readValue(svalue,s.exposure)) {
							std::cerr << "Problem reading Scene spp { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					} 
					else if (label == "antialising") {
						
						float v;
						if (!readValue(svalue,v)) {
							std::cerr << "Problem reading Scene antialising { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						s.antialising = (int)v;
						
					} 
					else if (label == "indirect") {
						
						float v;
						if (!readValue(svalue,v)) {
							std::cerr << "Problem reading Scene indirect { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						s.indirect = (v>0);
						
					} 
					else if (label == "direct") {
						
						float v;
						if (!readValue(svalue,v)) {
							std::cerr << "Problem reading Scene direct { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						s.direct = (v>0);
						
					} 
					else if (label == "iterations") {
						
						float v;
						if (!readValue(svalue,v)) {
							std::cerr << "Problem reading Scene antialising { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						s.iter = (int)v;
						
					} 
					

	}
	return true;
}
bool ConfigReader::parseMaterial(string& in, Material& m)
{
	string label,svalue;
	while(in.length() > 0 ){

					getLabel(in,label,in);
					getValue(in,svalue,in);

					
					if (label == "emission") {
						
						if (!readVector(svalue,m.e)) {
							std::cerr << "Problem reading Material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					} 
					else if (label == "diffuse") {
						
						if (!readVector(svalue,m.d)) {
							std::cerr << "Problem reading Material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					} 
					else if (label == "color") {
						
						if (!readVector(svalue,m.c)) {
							std::cerr << "Problem reading Material { " 
								<< label<< " " << svalue << " }" << endl;
							return false;
						}
						
					} 
					else  if (label =="rindex") {

						if (!readValue(svalue,m.rIndex)){
							std::cerr << "Problem reading Material { " 
								<< label << " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label =="specular") {

						if (!readVector(svalue,m.s)){
							std::cerr << "Problem reading Material { " 
								<< label << " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label =="power") {

						if (!readValue(svalue,m.n)){
							std::cerr << "Problem reading Material { " 
								<< label << " " << svalue << " }" << endl;
							return false;
						}
						
					}
					else if (label =="type") {
						stringstream s(svalue);
						string type;
						s >> type;
						if (!s){
							std::cerr << "Problem reading Material { " 
								<< label << " " << svalue << " }" << endl;
							return false;
						} else {
							if      (type =="refr" || type =="refraction") m.type = REFR;
							else if (type =="spec" || type =="specular")   m.type = SPEC;
							else if (type =="specp" || type == "specularphong") m.type = SPECP;
							else if (type =="dspec" || type == "diffusespecular") m.type = DSPEC;
							else     m.type = DIFF;
						}

						
					}

	}
	return true;
}

bool ConfigReader::getMaterial(string& label,string& svalue, Object& m, string t){
		if (label == t) {
						
						float code = 0;
						if (!readValue(svalue,code)) {
							return false;
						}
						if (code > _s.materials.size() -1 ){
							return false;
						}						
						m.material = _s.materials[(int)code];
		}
		return true;
}



void ConfigReader::parseObject( string in, string& label, string& rest ){

	size_t  start = in.find_first_of('{');
	size_t  last  = in.find_last_of('}');
	if (start == in.npos || last == in.npos) {
		label = "";
		rest  = "";
		return;
	}
	rest  = in.substr( start + 1, last - start-1);
	istringstream is (in.substr(0,start));
	is >> label;	
	
	transform(label.begin(),
				   label.end(),
				   label.begin(),
				   ::tolower);

	
}
void ConfigReader::getLabel( string in, string& label, string& rest ){
	size_t  start = in.find_first_of(':');
	if (start == in.npos) {
		label = "";
		rest  = "";
		return;
	}
	rest  = in.substr( start + 1, in.length()-1);
	istringstream is (in.substr(0,start));
	is >> label;	
	
	std::transform(label.begin(),
				   label.end(),
				   label.begin(),
				   ::tolower);
	
}
void ConfigReader::getValue( string in, string& value, string& rest ){

	size_t  start = in.find_first_of(';');
	rest  = in.substr( start + 1, in.length()-1);
	value = in.substr(0,start);	
	
}
bool ConfigReader::readVector(string& value, vec3& v){
	  size_t start = value.find_first_of('['); 
	  size_t last = value.find_last_of(']'); 
	  value = value.substr( start+1, last - start -1 );
	  start = value.find_first_of(',');
	  last  = value.find_last_of(',');
	  if (start == last ) return false;
	  istringstream is(value.substr( 0, start ));
	  is >> v.x;
	  if (!is) return false;
	  is.clear();
	  is.str(value.substr( start+1));
	  is >> v.y;
	  if (!is) return false;
	  is.clear();
	  is.str(value.substr(last+1));
	  is >> v.z;
	  if (!is) return false;
	  return true;
}
bool ConfigReader::readTuple(string& value, vec2& v){
	  size_t start = value.find_first_of('['); 
	  size_t last = value.find_last_of(']'); 
	  value = value.substr( start+1, last - start -1 );
	  start = value.find_first_of(',');
	 
	  istringstream is(value.substr( 0, start ));
	  is >> v.x;
	  if (!is) return false;
	  is.clear();
	  is.str(value.substr( start+1));
	  is >> v.y;

	  return true;
}
bool ConfigReader::readValue(string&  value, float& v){
      
	  istringstream is(value);
	  is >> v;	 
	  if (!is) return false;
	  return true;
}

#endif
