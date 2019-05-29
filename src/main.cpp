#include "global.h"
#include <iostream>
using namespace std;




int main(int argc, char** argv) {
	#if defined(__WIN32__)
	freopen("CON", "wb", stdout);
	freopen("CON", "wb", stderr);
	#endif
	printf("hello world\n");
	
	Display scr;
	scr.begin();
	// scr.mainloop();

	auto font = scr.loadBMP("ansi81.bmp");
	while (!scr.step()) {
		scr.buf.rect(10, 10, 50, 50, 0xff00ffff);
	}

	return scr.quit();	
}