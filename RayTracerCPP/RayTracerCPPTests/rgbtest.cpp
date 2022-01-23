#include "pch.h"
#include "rgb.h"

TEST(TestFloatToUint8, RgbTest) 
{
	RGB rgb(1.0, 0.5, 0.0);
	EXPECT_EQ(rgb.r, 255);
	EXPECT_EQ(rgb.g, 127);
	EXPECT_EQ(rgb.b, 0);
}