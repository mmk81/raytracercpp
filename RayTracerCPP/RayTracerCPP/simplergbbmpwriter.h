#pragma once

#include <string>

class RgbCanvas;

// Always stores in 24 bit RGB format without compression
class SimpleRgbBmpWriter
{
public:
	static void writeCanvasToFile(const RgbCanvas&, const std::string& path);
};

