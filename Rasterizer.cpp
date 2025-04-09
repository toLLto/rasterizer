#include "Rasterizer.hpp"
#include "RasTerX/include/MathUtils.hpp"
#include "TGA.hpp"
#include "Color.hpp"


Rasterizer::Rasterizer::Rasterizer(unsigned int width, unsigned int height) : colorBuffer(width, height)
{
}

void Rasterizer::Rasterizer::Render(const std::vector<Triangle> triangles, unsigned int backgroundColor)
{
	colorBuffer.SetBufferColorFill(backgroundColor);

	for (const Triangle& tr : triangles)
	{
		RenderTriangle(tr, 0xFFFFFFFF);
	}

	TGA::Save("miagk_3.tga", colorBuffer.GetColorBuffer(), colorBuffer.GetWidth(), colorBuffer.GetHeight());
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
	int acdx = ax - cx;
	int badx = bx - ax;
	int bcdx = bx - cx;
	int cadx = cx - ax;
	int cbdx = cx - bx;

	int abdy = ay - by;
	int acdy = ay - cy;
	int bady = by - ay;
	int bcdy = by - cy;
	int cady = cy - ay;
	int cbdy = cy - by;

	float uDenominator = 1.f / (bcdy * acdx + cbdx * acdy);
	float vDenominator = 1.f / (cady * bcdx + acdx * bcdy);

	for (int y = yMin; y < yMax; ++y)
	{
		for (int x = xMin; x < xMax; ++x)
		{
			int scdx = x - cx;
			int scdy = y - cy;

			float ab = abdx * (y - ay) - abdy * (x - ax);
			float bc = bcdx * (y - by) - bcdy * (x - bx);
			float ca = cadx * (y - cy) - cady * (x - cx);

			if (ab > 0 && bc > 0 && ca > 0)
			{
				float u = (bcdy * scdx + cbdx * scdy) * uDenominator;
				float v = (cady * scdx + acdx * scdy) * vDenominator;
				float w = 1.f - u - v;

				Color pColor(Color(RED).ToVector() * u + Color(GREEN).ToVector() * v + Color(BLUE).ToVector() * w);

				colorBuffer.SetPixel(x, y, pColor.ToHex());
			}
		}
	}
}
