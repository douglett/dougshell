#pragma once

#include <SDL/SDL.h>
#include <cassert>


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


} // end namespace