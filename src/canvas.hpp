#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>

class Canvas {
public:
	static const int 
		MIN_W = 2,
		MAX_W = 1024;

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
		// restrict size: multiples of 2, between MIN_W & max_W
		// this->w = int((w < MIN_W ? MIN_W : w > MAX_W ? MAX_W : w) / 2) * 2;
		// this->h = int((h < MIN_W ? MIN_W : h > MAX_W ? MAX_W : h) / 2) * 2;
		assert(w > 0 && h > 0);
		this->w = w, this->h = h;
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
};