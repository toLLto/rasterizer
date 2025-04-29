#pragma once

#include <vector>

class Buffer
{
private:
	const unsigned int width;
	const unsigned int height;

	std::vector<unsigned int> colorBuffer;
	std::vector<float> depthBuffer;

public:
	Buffer(unsigned int width, unsigned int height);
	~Buffer();

	unsigned int GetWidth() const { return width; }
	unsigned int GetHeight() const { return height; }

	unsigned int GetPixelColor(unsigned int x, unsigned int y) const;
	unsigned int GetPixelColor(unsigned int index) const;
	void SetPixelColor(unsigned int x, unsigned int y, unsigned int color);

	float GetPixelDepth(unsigned int x, unsigned int y) const;
	void SetPixelDepth(unsigned int x, unsigned int y, float depth);

	const std::vector<unsigned int>& GetColorBuffer() { return colorBuffer; }
	std::vector<unsigned int>& GetDirColorBuffer() { return colorBuffer; }
	const std::vector<float>& GetDepthBuffer() { return depthBuffer; }

	void SetBufferColorFill(unsigned int color);
	void SetBufferDepthFill(float depth);
};

