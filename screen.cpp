#include <SDL/SDL.h>
#include "global.h"
#include <cassert>
#include <map>
using namespace std;


namespace screen {

// public vars
// SDL event helper
const map<int, string> events = { 
	{ SDL_ACTIVEEVENT,      "SDL_ACTIVEEVENT" },
	{ SDL_KEYDOWN,          "SDL_KEYDOWN" },
	{ SDL_KEYUP,            "SDL_KEYUP" },
	{ SDL_MOUSEMOTION,      "SDL_MOUSEMOTION" },
	{ SDL_MOUSEBUTTONDOWN,  "SDL_MOUSEBUTTONDOWN" },
	{ SDL_MOUSEBUTTONUP,    "SDL_MOUSEBUTTONUP" },
	{ SDL_JOYAXISMOTION,    "SDL_JOYAXISMOTION" },
	{ SDL_JOYBALLMOTION,    "SDL_JOYBALLMOTION" },
	{ SDL_JOYHATMOTION,     "SDL_JOYHATMOTION" },
	{ SDL_JOYBUTTONDOWN,    "SDL_JOYBUTTONDOWN" },
	{ SDL_JOYBUTTONUP,      "SDL_JOYBUTTONUP" },
	{ SDL_VIDEORESIZE,      "SDL_VIDEORESIZE" },
	{ SDL_VIDEOEXPOSE,      "SDL_VIDEOEXPOSE" },
	{ SDL_QUIT,             "SDL_QUIT" },
	{ SDL_USEREVENT,        "SDL_USEREVENT" },
	{ SDL_SYSWMEVENT,       "SDL_SYSWMEVENT" },
};
// static
static const int S_FLAGS = SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE;
static Uint16 s_width = 640, s_height = 480;
static SDL_Surface* font = NULL;


int main() {
	setbuf(stdout, NULL); // stop buffering stdout. solves some windows printf issues
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(s_width, s_height, 32, S_FLAGS);

	// init
	SDL_Surface* bmp = SDL_LoadBMP("ansi81.bmp");
	SDL_Surface* bmp2 = SDL_ConvertSurface(bmp, SDL_GetVideoSurface()->format, 0);
	SDL_FreeSurface(bmp);
	font = bmp2;
	// printf("surface: %x %x\n", bmp2->format->Rmask, bmp2->format->Amask);

	int r = mainloop();

	SDL_Quit();
	return r;
}


int mainloop() {
	int doquit = 0;
	int dopaint = 0;
	SDL_Event e;

	// mainloop
	while (!doquit) {
		while (SDL_PollEvent(&e))
		switch (e.type) {
			// exit commands
			case SDL_QUIT:
				printf("Quitting app...\n");
				doquit = true;
				break;
			// rebuild screen
			case SDL_VIDEORESIZE:
				printf("resize: %d %d\n", e.resize.w, e.resize.h);
				s_width = e.resize.w;
				s_height = e.resize.h;
				SDL_SetVideoMode(s_width, s_height, 32, S_FLAGS);
				dopaint = 1;
				break;
			// repaint when screen changes focus
			case SDL_VIDEOEXPOSE:
				dopaint = 1;
				break;
			// just suppress these
			case SDL_ACTIVEEVENT:
			case SDL_MOUSEMOTION:
				break;
			// show unhandled
			default:
				printf("> 0x%02x :: %s\n", e.type, events.at(e.type).c_str());
		}

		// repaint screen if requested
		if (dopaint) {
			dopaint = 0;
			printf("paint...\n");
			SDL_Rect r = { 0, 0, s_width, s_height };
			SDL_FillRect(SDL_GetVideoSurface(), &r, 0x0);

			r = { 10, 10, 0, 0 };
			SDL_BlitSurface(font, NULL, SDL_GetVideoSurface(), &r);
			vprint(SDL_GetVideoSurface(), 100, 100, "Hello World!");

			scaleto(font, SDL_GetVideoSurface(), 3);
			SDL_Flip(SDL_GetVideoSurface());
		}
		SDL_Delay(16);
	}
	return 0;
}


void vprint(SDL_Surface* dst, int x, int y, const std::string& s) {
	if (!dst) dst = SDL_GetVideoSurface();
	SDL_Rect dr = { int16_t(x), int16_t(y), 0, 0 };
	SDL_Rect sr = { 0, 0, 4, 8 };
	for (char c : s) {
		sr.x = (c % 32) * 4;
		sr.y = int(c / 32) * 8;
		SDL_BlitSurface(font, &sr, dst, &dr);
		dr.x += 5;
	}
}


void scaleto(SDL_Surface* src, SDL_Surface* dst, int factor) {
	assert(src && dst && factor > 0); // sanity check
	// printf("scale: %d %d\n", dst->w, dst->pitch);
	SDL_Rect r = { 0, 0, uint16_t(factor), uint16_t(factor) };
	uint32_t* px = (uint32_t*)src->pixels;
	// do scale
	for (int y = src->h-1; y >= 0; y--)
	if (y*factor < dst->h)
	for (int x = src->w-1; x >= 0; x--)
	if (x*factor < dst->w) 
		r.x = x*factor, r.y = y*factor,
		SDL_FillRect(dst, &r, px[y * src->w + x]);
}


} // end gfx