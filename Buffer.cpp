#include "Buffer.hpp"

Buffer::Buffer(unsigned int width, unsigned int height) : width(width), height(height)
{
	colorBuffer.resize(width * height);
	depthBuffer.resize(width * height);
}

Buffer::~Buffer()
{
}

unsigned int Buffer::GetPixelColor(unsigned int x, unsigned int y) const
{
	return colorBuffer[x + width * y];
}

unsigned int Buffer::GetPixelColor(unsigned int index) const
{
	return colorBuffer[index];
}

void Buffer::SetPixelColor(unsigned int x, unsigned int y, unsigned int color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	colorBuffer[x + width * y] = color;
}

float Buffer::GetPixelDepth(unsigned int x, unsigned int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return FLT_MAX;
	}

	return depthBuffer[x + width * y];
}

void Buffer::SetPixelDepth(unsigned int x, unsigned int y, float depth)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	depthBuffer[x + width * y] = depth;
}

void Buffer::SetBufferColorFill(unsigned int color)
{
	for (int i = 0; i < width * height; ++i)
	{
		colorBuffer[i] = color;
	}
}

void Buffer::SetBufferDepthFill(float depth)
{
	for (int i = 0; i < width * height; ++i)
	{
		depthBuffer[i] = depth;
	}
}
