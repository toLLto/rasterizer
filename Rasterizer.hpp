#pragma once

#include "Buffer.hpp"
#include "RasTerX/include/Triangle.hpp"

using namespace rtx;

namespace Rasterizer
{
	class Rasterizer
	{
	private:
		Buffer colorBuffer;

	public:
		Rasterizer(unsigned int width, unsigned int height);

		void Render(const std::vector<Triangle> triangles, unsigned int backgroundColor);
		void Clear(unsigned int color = 0);

	private:
		void RenderTriangle(const Triangle triangle, unsigned int color);
	};
}

