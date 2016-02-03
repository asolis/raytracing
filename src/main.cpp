// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:main.cpp
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

#include <iostream>
#include <time.h>
#include "configreader.h"

using std::cout;
using std::endl;

int help(const string& message){
	cout << message << endl;
	cout << "Use: raytrace.exe scene.txt [output.tga]" << endl;
	return -1;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		return help("Missing arguments in command line.");
	}
   
	try {
		clock_t start, end;
		start = clock();

		ConfigReader r(argv[1]);
		Scene* a = r.parse();
		cout << *a << endl;
		
		if (argc == 2){
			string output(argv[1]);
			a->render(output.append(".tga"));
		}else
			a->render(argv[2]);

		end = clock();

		float sec = (float(end-start)/float(CLOCKS_PER_SEC));
		cout << "Running time: " << sec << " seconds. " << endl;
	} catch (string s) {
		return help(s);
	}
	
    return 0;
}

