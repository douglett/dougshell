#include "global.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv) {
	printf("hello world\n");
	Screen::begin();

	auto& w = Widgets::create("test1");
	// printf("%s %s\n", w.id.c_str(), w.parent.c_str());
	w.sf.resize(100, 100);
	w.x = w.y = 100;
	SDL_FillRect(w.sf.raw(), NULL, 0xff00ff);

	Screen::mainloop();
	return Screen::quit();
}