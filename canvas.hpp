#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Canvas {
public:
	static const int 
		MIN_W = 2,
		MAX_W = 1024;

	int w = 64, h = 64, activebuf = 1;
	std::vector<uint32_t> buf1, buf2;
	std::string id;

	// init
	Canvas() : buf1(w*h, 0), buf2(w*h, 0) { }
	Canvas(int w, int h) {
		if (w >= MIN_W && w <= MAX_W) this->w = w;
		if (h >= MIN_W && h <= MAX_W) this->h = h;
		buf1 = std::vector<uint32_t>(w*h, 0);
		buf2 = buf1;
	}

	// handle buffers
	std::vector<uint32_t>& mainbuf() { return activebuf == 1 ? buf1 : buf2; }
	std::vector<uint32_t>& backbuf() { return activebuf == 1 ? buf2 : buf1; }
	int flip() { return activebuf = (activebuf == 1 ? 2 : 1); }

	// basic painting
	int px(int x, int y, uint32_t col) {
		if (x >= 0 && x < w && y >= 0 && y < h)
			backbuf()[y*w+x] = col;
		return 0;
	}
	int rect(int rx, int ry, int rw, int rh, uint32_t col) {
		for (int i = ry; i < ry+rh; i++)
		for (int j = rx; j < rx+rw; j++)
			px(j, i, col);
		return 0;
	}
};