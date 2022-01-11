#include "simplergbbmpwriter.h"
#include "rgbcanvas.h"

#include <ostream>
#include <fstream>


namespace {
	const uint16_t BmpHeaderID = 0x4D42;
	const int BmpHeaderSize = 14;
	const int BitmapInfoHeaderSize = 40;
	const int BitsPerPixel = 24;
	const int BytesPerPixel = BitsPerPixel / 8;

	template<typename T>
	inline void writeField(std::ostream& os, const T& field)
	{
		os.write((const char*)&field, sizeof(T));
	}


	struct BmpHeader {
		uint16_t header;
		uint32_t fileSize;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t pixelDataOffset;

		explicit BmpHeader(int pixelDataSize) :
			header(BmpHeaderID),
			fileSize(pixelDataSize + BmpHeaderSize + BitmapInfoHeaderSize),
			reserved1(0),
			reserved2(0),
			pixelDataOffset(BmpHeaderSize + BitmapInfoHeaderSize)
		{

		}

		void serialize(std::ostream& os)
		{
			writeField(os, header);
			writeField(os, fileSize);
			writeField(os, reserved1);
			writeField(os, reserved2);
			writeField(os, pixelDataOffset);
		}
	};

	struct BitmapInfoHeader {
		uint32_t headerSize;
		int32_t bitmapWidth;
		int32_t bitmapHeight;
		uint16_t nrOfPlanes; // Must be 1
		uint16_t nrOfBitsPerPixel;
		uint32_t compressionMethod; // Not supported, 0
		uint32_t imageSize;
		int32_t horizontalResolution;
		int32_t verticalResolution;
		uint32_t nrOfColorsInPalette;
		uint32_t nrOfImportantColors; // Typically 0

		BitmapInfoHeader(int width, int height, int pixelDataSize) :
			headerSize(BitmapInfoHeaderSize),
			bitmapWidth(width),
			bitmapHeight(height),
			nrOfPlanes(1),
			nrOfBitsPerPixel(BitsPerPixel),
			compressionMethod(0),
			imageSize(pixelDataSize),
			horizontalResolution(0),
			verticalResolution(0),
			nrOfColorsInPalette(0),
			nrOfImportantColors(0)
		{

		}

		void serialize(std::ostream& os)
		{
			writeField(os, headerSize);
			writeField(os, bitmapWidth);
			writeField(os, bitmapHeight);
			writeField(os, nrOfPlanes);
			writeField(os, nrOfBitsPerPixel);
			writeField(os, compressionMethod);
			writeField(os, imageSize);
			writeField(os, horizontalResolution);
			writeField(os, verticalResolution);
			writeField(os, nrOfColorsInPalette);
			writeField(os, nrOfImportantColors);
		}
	};

}

void SimpleRgbBmpWriter::writeCanvasToFile(const RgbCanvas& canvas, const std::string& path)
{
	std::ofstream os(path, std::ofstream::out | std::ofstream::binary);

	int width = canvas.width();
	int height = canvas.height();
	int stride = static_cast<int>((BitsPerPixel * width + 31) / 32) * 4;

	const auto& pixels = canvas.pixels();
	
	int pixelDataSize = stride * height;
	BmpHeader bmpHeader(pixelDataSize);
	BitmapInfoHeader bmpInfoHeader(width, height, pixelDataSize);

	bmpHeader.serialize(os);
	bmpInfoHeader.serialize(os);

	// BMP stores last line first
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			const auto& pixel = pixels[y * width + x];
			os.write((const char*)&pixel.b, 1);
			os.write((const char*)&pixel.g, 1);
			os.write((const char*)&pixel.r, 1);
		}

		int padding = 0;
		os.write((const char*)&padding, stride - (width * BytesPerPixel));
	}
	
}








