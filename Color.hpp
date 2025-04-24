#pragma once

#include "RasTerX/include/Vector3.hpp"

const unsigned int BLACK = 0xFF000000;
const unsigned int WHITE = 0xFFFFFFFF;
const unsigned int GRAY = 0xFF808080;
const unsigned int RED = 0xFFFF0000;
const unsigned int GREEN = 0xFF00FF00;
const unsigned int BLUE = 0xFF0000FF;
const unsigned int YELLOW = 0xFFFFFF00;
const unsigned int MAGENTA = 0xFFFF00FF;
const unsigned int CYAN = 0xFF00FFFF;

struct Color
{
	unsigned char r, g, b, a;

	Color();
	Color(int r, int g, int b, int a = 255);
	explicit Color(float r, float g, float b, float a = 1.0f);
	Color(unsigned int hex);
	Color(rtx::Vector3 v, const float a = 1.0f);

	unsigned int ToHex() const;

	rtx::Vector3 ToVector() const;
};