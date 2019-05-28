#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Canvas {
public:
	static const int 
		MIN_W = 2,
		MAX_W = 1024;

	int w = 64, h = 64;
	std::vector<uint32_t> buf;
	std::string id;

	// init
	Canvas() : buf(w*h, 0) { }
	Canvas(int w, int h) {
		if (w >= MIN_W && w <= MAX_W) this->w = int(w/2)*2;
		if (h >= MIN_W && h <= MAX_W) this->h = int(h/2)*2;
		buf = std::vector<uint32_t>(this->w*this->h, 0);
	}

	// basic painting
	int px(int x, int y, uint32_t col) {
		if (x >= 0 && x < w && y >= 0 && y < h)
			buf[y*w+x] = col;
		return 0;
	}
	int rect(int rx, int ry, int rw, int rh, uint32_t col) {
		for (int i = ry; i < ry+rh; i++)
		for (int j = rx; j < rx+rw; j++)
			px(j, i, col);
		return 0;
	}
};