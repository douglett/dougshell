#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <algorithm>

class Canvas {
public:
	// static const int 
	// 	MIN_W = 2,
	// 	MAX_W = 1024;

	int w = 64, h = 64;
	std::vector<uint32_t> buf;
	std::string id;

	// init
	Canvas() {
		resize(w, h);
	}
	Canvas(int w, int h) {
		resize(w, h);
	}
	int resize(int w, int h) {
		this->w = std::max(w, 0), this->h = std::max(h, 0);
		buf = std::vector<uint32_t>(this->w * this->h, 0);
		return 0;
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
	uint32_t peek(int x, int y) const {
		if (x >= 0 && x < w && y >= 0 && y < h)
			return buf[y * w + x];
		return 0;
	}

	// copying
	int blit(int x, int y, const Canvas& c) {
		for (int yy = 0; yy < c.h; yy++)
		for (int xx = 0; xx < c.w; xx++)
			px(x + xx, y + yy, c.peek(xx, yy));
		return 0;
	}
};