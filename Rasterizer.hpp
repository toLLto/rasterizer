#pragma once

#include "Buffer.hpp"
#include "RasTerX/include/Triangle.hpp"
#include "RasTerX/include/Matrix4.hpp"

using namespace rtx;

class Rasterizer
{
private:
	Buffer buffer;
	float fov;
	float aspect;
	float near;
	float far;

public:
	Rasterizer(unsigned int width, unsigned int height, float fov, float aspect, float near = 0.01f, float far = 100.f);

	void Render(const std::vector<Triangle>& triangles, const rtx::Matrix4& model, unsigned int backgroundColor);
	void ClearBufferColor(unsigned int color = 0);
	void ClearBufferDepth(float depth = FLT_MAX);

private:
	void RenderTriangle(const Triangle triangle, const rtx::Matrix4& model, unsigned int color);
};

