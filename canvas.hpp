#pragma once
#include <vector>
#include <cstdint>

class Canvas {
public:
	static const int 
		MIN_W = 2,
		MAX_W = 1024;

	int w = 64, h = 64;
	std::vector<uint32_t> buf1, buf2;
	Canvas() : buf1(w*h, 0), buf2(w*h, 0) { }
	Canvas(int w, int h) {
		if (w >= MIN_W && w <= MAX_W) this->w = w;
		if (h >= MIN_W && h <= MAX_W) this->h = h;
		buf1 = std::vector<uint32_t>(w*h, 0);
		buf2 = buf1;
	}
};