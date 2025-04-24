#include "Color.hpp"
#include "RasTerX/include/MathUtils.hpp"

Color::Color() : r(0), g(0), b(0), a(0xFF)
{
}

Color::Color(int r, int g, int b, int a)
{
	r = static_cast<unsigned char>(rtx::MathUtils::Clamp(r, 0, 255));
	g = static_cast<unsigned char>(rtx::MathUtils::Clamp(g, 0, 255));
	b = static_cast<unsigned char>(rtx::MathUtils::Clamp(b, 0, 255));
	a = static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0, 255));
}

Color::Color(float r, float g, float b, float a)
{
	this->r = static_cast<unsigned char>(rtx::MathUtils::Clamp(r, 0.0f, 1.0f) * 255);
	this->g = static_cast<unsigned char>(rtx::MathUtils::Clamp(g, 0.0f, 1.0f) * 255);
	this->b = static_cast<unsigned char>(rtx::MathUtils::Clamp(b, 0.0f, 1.0f) * 255);
	this->a = static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0.0f, 1.0f) * 255);
}

Color::Color(unsigned int hex)
{
	a = (hex >> 24) & 0xFF;
	r = (hex >> 16) & 0xFF;
	g = (hex >> 8) & 0xFF;
	b = hex & 0xFF;
}

Color::Color(rtx::Vector3 v, const float a) : a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0.0f, 1.0f) * 255))
{
	r = static_cast<unsigned char>(rtx::MathUtils::Clamp(v.x, 0.0f, 1.0f) * 255);
	g = static_cast<unsigned char>(rtx::MathUtils::Clamp(v.y, 0.0f, 1.0f) * 255);
	b = static_cast<unsigned char>(rtx::MathUtils::Clamp(v.z, 0.0f, 1.0f) * 255);
}

unsigned int Color::ToHex() const
{
	return a << 24 | r << 16 | g << 8 | b;
}

rtx::Vector3 Color::ToVector() const
{
	return rtx::Vector3(
		static_cast<float>(r) / 255.0f,
		static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f
	);
}
