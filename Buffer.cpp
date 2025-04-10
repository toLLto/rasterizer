#include "Buffer.hpp"

Rasterizer::Buffer::Buffer(unsigned int width, unsigned int height) : width(width), height(height)
{
	colorBuffer.resize(width * height);
	depthBuffer.resize(width * height);
}

Rasterizer::Buffer::~Buffer()
{
}

unsigned int Rasterizer::Buffer::GetPixelColor(unsigned int x, unsigned int y) const
{
	return colorBuffer[x + width * y];
}

void Rasterizer::Buffer::SetPixelColor(unsigned int x, unsigned int y, unsigned int color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	colorBuffer[x + width * y] = color;
}

float Rasterizer::Buffer::GetPixelDepth(unsigned int x, unsigned int y) const
{
	return depthBuffer[x + width * y];
}

void Rasterizer::Buffer::SetPixelDepth(unsigned int x, unsigned int y, float depth)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	depthBuffer[x + width * y] = depth;
}

void Rasterizer::Buffer::SetBufferColorFill(unsigned int color)
{
	for (int i = 0; i < width * height; ++i)
	{
		colorBuffer[i] = color;
	}
}

void Rasterizer::Buffer::SetBufferDepthFill(float depth)
{
	for (int i = 0; i < width * height; ++i)
	{
		depthBuffer[i] = depth;
	}
}
