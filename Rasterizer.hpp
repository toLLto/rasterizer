#pragma once

#include "Buffer.hpp"
#include "RasTerX/include/Triangle.hpp"

using namespace rtx;

namespace Rasterizer
{
	class Rasterizer
	{
	private:
		Buffer buffer;

	public:
		Rasterizer(unsigned int width, unsigned int height);

		void Render(const std::vector<Triangle> triangles, unsigned int backgroundColor);
		void ClearBufferColor(unsigned int color = 0);
		void ClearBufferDepth(float depth = FLT_MAX);

	private:
		void RenderTriangle(const Triangle triangle, unsigned int color);
	};
}

