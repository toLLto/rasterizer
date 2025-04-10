#include "Rasterizer.hpp"
#include "RasTerX/include/MathUtils.hpp"
#include "TGA.hpp"
#include "Color.hpp"


Rasterizer::Rasterizer::Rasterizer(unsigned int width, unsigned int height) : buffer(width, height)
{
}

void Rasterizer::Rasterizer::Render(const std::vector<Triangle> triangles, unsigned int backgroundColor)
{
	buffer.SetBufferColorFill(backgroundColor);
	buffer.SetBufferDepthFill(FLT_MAX);

	for (const Triangle& tr : triangles)
	{
		RenderTriangle(tr, 0xFFFFFFFF);
	}

	TGA::Save("miagk_4.tga", buffer.GetColorBuffer(), buffer.GetWidth(), buffer.GetHeight());
}

void Rasterizer::Rasterizer::ClearBufferColor(unsigned int color)
{
	buffer.SetBufferColorFill(color);
}

void Rasterizer::Rasterizer::ClearBufferDepth(float depth)
{
	buffer.SetBufferDepthFill(depth);
}

void Rasterizer::Rasterizer::RenderTriangle(const Triangle triangle, unsigned int color)
{
	int width = buffer.GetWidth();
	int height = buffer.GetHeight();

	int ax = (triangle.GetVertA().x + 1.f) * width * 0.5f;
	int ay = (triangle.GetVertA().y + 1.f) * height * 0.5f;
	float az = triangle.GetVertA().z;

	int bx = (triangle.GetVertB().x + 1.f) * width * 0.5f;
	int by = (triangle.GetVertB().y + 1.f) * height * 0.5f;
	float bz = triangle.GetVertB().z;

	int cx = (triangle.GetVertC().x + 1.f) * width * 0.5f;
	int cy = (triangle.GetVertC().y + 1.f) * height * 0.5f;
	float cz = triangle.GetVertC().z;

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

	bool topLeft1 = (abdy < 0 || (abdy == 0 && abdx > 0));
	bool topLeft2 = (bcdy < 0 || (bcdy == 0 && bcdx > 0));
	bool topLeft3 = (cady < 0 || (cady == 0 && cadx > 0));

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

			if ((ab > 0 || (ab >= 0 && topLeft1)) && (bc > 0 || (bc >= 0 && topLeft2)) && (ca > 0 || (ca >= 0 && topLeft3)))
			{
				float u = (bcdy * scdx + cbdx * scdy) * uDenominator;
				float v = (cady * scdx + acdx * scdy) * vDenominator;
				float w = 1.f - u - v;

				float sDepth = buffer.GetPixelDepth(x, y);
				float pDepth = u * az + v * bz + w * cz;

				if (pDepth < sDepth)
				{
					Vector3 pColor = Color(RED).ToVector() * u + Color(GREEN).ToVector() * v + Color(BLUE).ToVector() * w;

					buffer.SetPixelColor(x, y, Color(pColor).ToHex());
					buffer.SetPixelDepth(x, y, pDepth);
				}
			}
		}
	}
}
