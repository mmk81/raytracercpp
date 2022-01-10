#include "rgb.h"

#include <algorithm>

namespace {
	template<typename T>
	inline uint8_t realToUint8(T val)
	{
		return static_cast<uint8_t>(std::max(0.0, std::min(255.0, 255.999 * val)));
	}
}

RGB::RGB() :
	r(0),
	g(0),
	b(0)
{

}

RGB::RGB(uint8_t r_, uint8_t g_, uint8_t b_) :
	r(r_),
	g(g_),
	b(b_)
{

}

RGB::RGB(double r_, double g_, double b_) :
	r(realToUint8(r_)),
	g(realToUint8(g_)),
	b(realToUint8(b_))
{

}
