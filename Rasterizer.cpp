#include "Rasterizer.hpp"
#include "RasTerX/include/MathUtils.hpp"
#include "TGA.hpp"

Rasterizer::Rasterizer::Rasterizer(unsigned int width, unsigned int height) : colorBuffer(width, height)
{
}

void Rasterizer::Rasterizer::Render(unsigned int backgroundColor)
{
	colorBuffer.SetBufferColorFill(backgroundColor);

	TGA::Save("miagk_1.tga", colorBuffer.GetColorBuffer(), colorBuffer.GetWidth(), colorBuffer.GetHeight());
}

void Rasterizer::Rasterizer::Clear(unsigned int color)
{
	colorBuffer.SetBufferColorFill(color);
}
