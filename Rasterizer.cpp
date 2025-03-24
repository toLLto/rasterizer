#include "Rasterizer.hpp"
#include "RasTerX/include/MathUtils.hpp"
#include "TGA.hpp"

Rasterizer::Rasterizer::Rasterizer(unsigned int width, unsigned int height) : colorBuffer(width, height)
{
}

void Rasterizer::Rasterizer::Render(Triangle triangle, unsigned int triangleColor, unsigned int backgroundColor)
{
	colorBuffer.SetBufferColorFill(backgroundColor);

	RenderTriangle(triangle, triangleColor);

	TGA::Save("miagk_2.tga", colorBuffer.GetColorBuffer(), colorBuffer.GetWidth(), colorBuffer.GetHeight());
}

void Rasterizer::Rasterizer::Clear(unsigned int color)
{
	colorBuffer.SetBufferColorFill(color);
}

void Rasterizer::Rasterizer::RenderTriangle(const Triangle triangle, unsigned int color)
{
	int width = colorBuffer.GetWidth();
	int height = colorBuffer.GetHeight();

	int ax = (triangle.GetVertA().x + 1.f) * width * 0.5f;
	int ay = (triangle.GetVertA().y + 1.f) * height * 0.5f;

	int bx = (triangle.GetVertB().x + 1.f) * width * 0.5f;
	int by = (triangle.GetVertB().y + 1.f) * height * 0.5f;

	int cx = (triangle.GetVertC().x + 1.f) * width * 0.5f;
	int cy = (triangle.GetVertC().y + 1.f) * height * 0.5f;

	int xMin = std::max(MathUtils::Min3<int>(ax, bx, cx), 0);
	int yMin = std::max(MathUtils::Min3<int>(ay, by, cy), 0);

	int xMax = std::max(MathUtils::Max3<int>(ax, bx, cx), width);
	int yMax = std::max(MathUtils::Max3<int>(ay, by, cy), height);

	int abdx = ax - bx;
	int bcdx = bx - cx;
	int cadx = cx - ax;

	int abdy = ay - by;
	int bcdy = by - cy;
	int cady = cy - ay;

	for (int y = yMin; y < yMax; ++y)
	{
		for (int x = xMin; x < xMax; ++x)
		{
			float ab = abdx * (y - ay) - abdy * (x - ax);
			float bc = bcdx * (y - by) - bcdy * (x - bx);
			float ca = cadx * (y - cy) - cady * (x - cx);

			if (ab > 0 && bc > 0 && ca > 0)
			{
				colorBuffer.SetPixel(x, y, color);
			}
		}
	}
}
