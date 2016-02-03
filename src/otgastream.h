// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:otgastream.h
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
