#include "global.h"
#include <cassert>
using namespace std;


namespace Widgets {


// surface hander class
class Surface {
private:
	SDL_Surface* sf = NULL;
public:
	// memory handers
	Surface() { resize(10, 10); }
	Surface(int w, int h) { resize(w, h); }
	~Surface() { SDL_FreeSurface(sf); }
	Surface(const Surface& other) { clone(other.sf); }
	Surface& operator=(const Surface& other) { clone(other.sf); return *this; }
	SDL_Surface* raw() { return sf; }
	// surface hander
	void resize(int w, int h) {
		assert(w > 0 && h > 0);
		SDL_FreeSurface(sf);
		SDL_PixelFormat* fmt = SDL_GetVideoSurface()->format;
		sf = SDL_CreateRGBSurface(
			SDL_SWSURFACE, w, h, 32,
			fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask );
	}
	void clone(const SDL_Surface* sf2) {
		SDL_FreeSurface(sf);
		sf = SDL_CreateRGBSurfaceFrom(
			sf2->pixels, sf2->w, sf2->h, sf2->format->BitsPerPixel, sf2->pitch,
			sf2->format->Rmask, sf2->format->Gmask, sf2->format->Bmask, sf2->format->Amask );
	}
};


// widget handler class
class Widget {
private:
public:
	Surface sf;
	int x = 0, y = 0;
	int width () { return sf.raw()->w; }
	int height() { return sf.raw()->h; }
};


// holders
static vector<Widget> WidgetList;


void paint() {
	if (!WidgetList.size()) {
		WidgetList.push_back(Widget());
		auto& w = WidgetList.back();
		w.sf.resize(50, 50);
		w.x = 30, w.y = 30;
		SDL_FillRect(w.sf.raw(), NULL, 0xff00ff);
	}

	SDL_Surface* dst = SDL_GetVideoSurface();
	SDL_Rect r = { 0 };
	for (auto w : WidgetList)
		r.x = w.x, r.y = w.y,
		SDL_BlitSurface(w.sf.raw(), NULL, dst, &r);
}


} // end namespace