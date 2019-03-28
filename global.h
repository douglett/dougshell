#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <vector>

namespace screen {
	int  main();
	int  mainloop();
	void vprint(SDL_Surface* dst, int x, int y, const std::string& s);
	void scaleto(SDL_Surface* src, SDL_Surface* dst, int factor);
}

namespace widgets {
	void paint();
}