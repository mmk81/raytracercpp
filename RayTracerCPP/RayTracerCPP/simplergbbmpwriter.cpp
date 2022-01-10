#include "simplergbbmpwriter.h"

#include <stdint.h>
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

SimpleRgbBmpWriter::SimpleRgbBmpWriter(int width, int height) :
	m_width(width),
	m_stride(0),
	m_height(height),
	m_colordata()
{
	m_stride = (BitsPerPixel * width + 31) / 32;
	m_stride *= 4;
	m_colordata.resize(m_width * m_height);
}

SimpleRgbBmpWriter::~SimpleRgbBmpWriter()
{

}

void SimpleRgbBmpWriter::writeToFile(const std::string& path)
{
	std::ofstream os(path, std::ofstream::out | std::ofstream::binary);

	int pixelDataSize = m_stride * m_height;
	BmpHeader bmpHeader(pixelDataSize);
	BitmapInfoHeader bmpInfoHeader(m_width, m_height, pixelDataSize);

	bmpHeader.serialize(os);
	bmpInfoHeader.serialize(os);

	// BMP stores last line first
	for (int y = m_height - 1; y >= 0; y--)
	{
		for (int x = 0; x < m_width; x++)
		{
			const auto& pixel = m_colordata[colorDataIndex(x, y)];
			os.write((const char*)&pixel.b, 1);
			os.write((const char*)&pixel.g, 1);
			os.write((const char*)&pixel.r, 1);
		}

		int padding = 0;
		os.write((const char*)&padding, m_stride - (m_width * BytesPerPixel));
	}
}

void SimpleRgbBmpWriter::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	int idx = colorDataIndex(x, y);
	m_colordata[idx].r = r;
	m_colordata[idx].g = g;
	m_colordata[idx].b = b;
}

void SimpleRgbBmpWriter::setPixel(int x, int y, SimpleRgbBmpWriter::RGB rgb)
{
	int idx = colorDataIndex(x, y);
	m_colordata[idx] = rgb;
}

int SimpleRgbBmpWriter::colorDataIndex(int x, int y)
{
	return y * m_width + x;
}

std::vector<SimpleRgbBmpWriter::RGB>::iterator SimpleRgbBmpWriter::getIterator(int x, int y)
{
	return m_colordata.begin() + colorDataIndex(x, y);
}




