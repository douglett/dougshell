#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "widgets_surface.hpp"
#include "widgets_widget.hpp"

namespace Screen {
	int  begin();
	int  quit();
	int  mainloop();
	void vprint(SDL_Surface* dst, int x, int y, const std::string& s);
	void scaleto(SDL_Surface* src, SDL_Surface* dst, int factor);
}

namespace Widgets {
	extern std::vector<Widget> WidgetList;
	Widget& create(const std::string& id, const std::string& parent = "root");
	int gc();
	int paint();
}