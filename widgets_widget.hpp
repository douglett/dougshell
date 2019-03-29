#pragma once
#include "widgets_surface.hpp"
#include <string>


namespace Widgets {


// widget handler class
class Widget {
private:
public:
	Surface sf;
	int x = 0, y = 0;
	std::string parent = "root";
	std::string id;
	int width () { return sf.raw()->w; }
	int height() { return sf.raw()->h; }
	int resize(int w, int h) { return sf.resize(h, w), 0; }
};


} // end namespace