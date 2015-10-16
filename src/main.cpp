// ==========================================================================
// Final Project (CSI5146): raytracer
// Description:main.cpp
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

