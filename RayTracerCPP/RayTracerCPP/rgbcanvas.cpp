#include "rgbcanvas.h"


RgbCanvas::RgbCanvas(int width, int height) :
	m_width(width),
	m_height(height),
	m_pixels(width * height)
{

}

void RgbCanvas::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	int idx = toPixelIndex(x, y);
	m_pixels[idx].r = r;
	m_pixels[idx].g = g;
	m_pixels[idx].b = b;
}

void RgbCanvas::setPixel(int x, int y, RGB rgb)
{
	int idx = toPixelIndex(x, y);
	m_pixels[idx] = rgb;
}

const std::vector<RGB>& RgbCanvas::pixels() const
{
	return m_pixels;
}

int RgbCanvas::width() const
{
	return m_width;
}

int RgbCanvas::height() const
{
	return m_height;
}

int RgbCanvas::toPixelIndex(int x, int y)
{
	return y * m_width + x;
}