#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include <iterator>
#include "rgb.h"

// Always stores in 24 bit RGB format without compression
class SimpleRgbBmpWriter
{
public:
	SimpleRgbBmpWriter(int width, int height);
	virtual ~SimpleRgbBmpWriter();

	void writeToFile(const std::string& path);
	void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void setPixel(int x, int y, RGB rgb);

	std::vector<RGB>::iterator getIterator(int x, int y);

private:
	int colorDataIndex(int x, int y);

private:
	int m_width;
	int m_stride;
	int m_height;
	// Pixel data (RGB) to store. Note this does not include padding pixels and starts at first row (when writing BMP last row is saved first)
	std::vector<RGB> m_colordata;
};

