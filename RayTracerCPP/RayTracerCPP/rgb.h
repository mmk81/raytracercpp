#pragma once

#include <stdint.h>

class RGB
{
public:
	RGB();
	RGB(uint8_t r, uint8_t g, uint8_t b);
	RGB(double r, double g, double b);
	~RGB() = default;

public:
	uint8_t r, g, b;
};

