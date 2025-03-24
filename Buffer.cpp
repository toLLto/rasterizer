#include "Buffer.hpp"

Rasterizer::Buffer::Buffer(unsigned int width, unsigned int height) : width(width), height(height)
{
	colorBuffer.resize(width * height);
}

Rasterizer::Buffer::~Buffer()
{
}

unsigned int Rasterizer::Buffer::GetPixel(unsigned int x, unsigned int y) const
{
	return colorBuffer[x + width * y];
}

void Rasterizer::Buffer::SetPixel(unsigned int x, unsigned int y, unsigned int color)
{
	colorBuffer[x + width * y] = color;
}

void Rasterizer::Buffer::SetBufferColorFill(unsigned int color)
{
	for (int i = 0; i < width * height; ++i)
	{
		colorBuffer[i] = color;
	}
}
