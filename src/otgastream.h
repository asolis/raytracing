// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:otgastream.h
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

#ifndef OTGASTREAM_H
#define OTGASTREAM_H


#include <string>
#include <fstream>
#include <math.h>
#include "vec3.h"

using std::ofstream;
using std::string;


// Following implementation of Paul Bourke 1996 as explainned
// in webpage "Creating TGA Image Files"
// http://local.wasp.uwa.edu.au/~pbourke/dataformats/tga/
class otgastream: public ofstream{
	
	int _w;
	int _h;

	public:
	otgastream(string fileName,int width, int height): 
												ofstream(fileName.c_str(),ios_base::binary),
		                                        _w(width),_h(height) {
		if (!(*this)) {
			throw string("File cannot be opened for writing:" )+= fileName;
		}
		
		put(0);
		put(0);
		put(2);  /*uncompresed RGB*/
		put(0); 
		put(0);
		put(0); 
		put(0);
		put(0);
		put(0); put(0);           /* X origin */
		put(0); put(0);           /* y origin */
		put((unsigned char)(_w & 0x00FF));
		put((unsigned char)((_w & 0xFF00) / 256));
		put((unsigned char)(_h & 0x00FF));
		put((unsigned char)((_h & 0xFF00) / 256));
		put(24);                        /* 24 bit bitmap */
		put(0);
	}

	void putInt(int rgb){
		unsigned char b = (rgb & 0xFF);
		unsigned char g = (rgb >> 8) & 0xFF;
		unsigned char r = (rgb >> 16) & 0xFF;
		put(b);put(g);put(r);
	}
													
	// The order is blue,green,red  just RGB.reverse ;)
	void putV(vec3 v){
		put((unsigned char)std::min(v.z*255.0,255.0));
		put((unsigned char)std::min(v.y*255.0,255.0));
		put((unsigned char)std::min(v.x*255.0,255.0));
	}

};


#endif
