#include "global.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv) {
	#if defined(__WIN32__)
	freopen("CON", "wb", stdout);
	freopen("CON", "wb", stderr);
	#endif
	printf("hello world\n");
	Screen::begin();

	
	Screen::mainloop();
	return Screen::quit();
}