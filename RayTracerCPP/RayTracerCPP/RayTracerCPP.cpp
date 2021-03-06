#include <iostream>
#include "simplergbbmpwriter.h"
#include "rgbcanvas.h"

void writeTestBmp()
{
    const int image_width = 256;
    const int image_height = 256;

    RgbCanvas canvas(image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            canvas.setPixel(i, j, RGB(r, g, b));
        }
    }

    SimpleRgbBmpWriter::writeCanvasToFile(canvas, "d:\\temp\\first.bmp");
}

int main()
{
    writeTestBmp();
    return 0;
}
