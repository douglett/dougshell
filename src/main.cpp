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
		scr.buf.rect(10, 10, 550, 550, 0xff00ffff);
		scr.buf.blit(50, 50, font);
	}

	return scr.quit();	
}