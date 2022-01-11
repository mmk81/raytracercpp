#pragma once

#include "rgb.h"
#include <vector>

class RgbCanvas
{
public:
	RgbCanvas(int width, int height);
	~RgbCanvas() = default;

	void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void setPixel(int x, int y, RGB rgb);

	int width() const;
	int height() const;
	const std::vector<RGB>& pixels() const;

private:
	int toPixelIndex(int x, int y);

private:
	int m_width;
	int m_height;
	std::vector<RGB> m_pixels;

};