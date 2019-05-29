#pragma once
#include "global.h"
#include "canvas.hpp"
#include <cassert>
#include <map>

class Display {
// const public vars
public:
	// SDL event helper
	const std::map<int, std::string> events = { 
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
	// static vars
	// const int S_FLAGS = SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE;
	const int S_FLAGS = SDL_SWSURFACE | SDL_RESIZABLE;

// useful private vars
private:
	Uint16 s_width = 640, s_height = 480;
	SDL_Surface *vbuffer = NULL;

// main interfact
public:
	Canvas buf;

	int begin() {
		setbuf(stdout, NULL); // stop buffering stdout. solves some windows printf issues
		SDL_Init(SDL_INIT_VIDEO);
		resizeScreen(s_width, s_height);
		return 0;
	}
	int quit() {
		SDL_Quit();
		return 0;
	}

	Canvas loadBMP(const std::string& fname) {
		SDL_Surface* bmp = SDL_LoadBMP(fname.c_str());
		if (!bmp) {
			fprintf(stderr, "error opening file: %s\n", fname.c_str());
			return Canvas();
		}
		SDL_Surface* bmp2 = SDL_ConvertSurface(bmp, vbuffer->format, 0);
		Canvas c(bmp2->w, bmp2->h);
		memcpy( &c.buf[0], bmp2->pixels, bmp2->w * bmp2->h * 4 );
		SDL_FreeSurface(bmp);
		SDL_FreeSurface(bmp2);
		return c;
	}

	int mainloop() {
		// mainloop
		while (true) {
			if (step())
				break;
		}
		return 0;
	}

	int step() {
		int doquit = 0;
		// handle events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		switch (e.type) {
			// exit commands
			case SDL_QUIT:
				printf("Quitting app...\n");
				doquit = 1;
				break;
			// rebuild screen
			case SDL_VIDEORESIZE:
				printf("resize: %d %d\n", e.resize.w, e.resize.h);
				resizeScreen(e.resize.w, e.resize.h);
				// dopaint = 1;
				break;
			// repaint when screen changes focus
			case SDL_VIDEOEXPOSE:
				// dopaint = 1;
				break;
			// just suppress these
			case SDL_ACTIVEEVENT:
			case SDL_MOUSEMOTION:
				break;
			// show unhandled
			// default:
			// 	printf("> 0x%02x :: %s\n", e.type, events.at(e.type).c_str());
		}
		// repaint screen
		SDL_FillRect(SDL_GetVideoSurface(), NULL, 0x0);
		memcpy( vbuffer->pixels, &buf.buf[0], s_width*s_height*4 ); // paint canvas to backbuffer
		SDL_BlitSurface(vbuffer, NULL, SDL_GetVideoSurface(), NULL); // flip backbuffer to screen
		SDL_Flip(SDL_GetVideoSurface()); // flip screen
		SDL_Delay(16); // wait 1 frame

		return doquit;
	}


// helpers
private:
	int resizeScreen(int w, int h) {
		s_width = w, s_height = h;
		SDL_SetVideoMode(s_width, s_height, 32, S_FLAGS);
		buf.resize(s_width, s_height);
		SDL_FreeSurface(vbuffer);
		vbuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, s_width, s_height, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
		return 0;
	}

};


// void vprint(SDL_Surface* dst, int x, int y, const std::string& s) {
// 	if (!dst) dst = SDL_GetVideoSurface();
// 	SDL_Rect dr = { int16_t(x), int16_t(y), 0, 0 };
// 	SDL_Rect sr = { 0, 0, 4, 8 };
// 	for (char c : s) {
// 		sr.x = (c % 32) * 4;
// 		sr.y = int(c / 32) * 8;
// 		SDL_BlitSurface(font, &sr, dst, &dr);
// 		dr.x += 5;
// 	}
// }