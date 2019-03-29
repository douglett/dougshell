#include "global.h"
#include <cassert>
using namespace std;


namespace Widgets {


// holders
std::vector<Widget> WidgetList;


Widget& create(const std::string& id, const std::string& parent) {
	WidgetList.emplace_back();
	auto& w = WidgetList.back();
	w.id = id;
	w.parent = parent;
	return w;
}


int gc() {
	int count = 0;
	for (int i = WidgetList.size()-1; i >= 0; i--)
		if (WidgetList[i].parent == "" || WidgetList[i].id == "")
			WidgetList.erase(WidgetList.begin()+i), count++;
	return count;
}


int paint() {
	SDL_Surface* dst = SDL_GetVideoSurface();
	SDL_Rect r = { 0 };
	for (auto& w : WidgetList)
		r.x = w.x, r.y = w.y,
		SDL_BlitSurface(w.sf.raw(), NULL, dst, &r);
	return 0;
}


} // end namespace