#pragma once

#include "Buffer.hpp"
#include "RasTerX/include/Triangle.hpp"
#include "RasTerX/include/Matrix4.hpp"
#include "Mesh.hpp"
#include <memory>

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

	void Render(std::vector<Mesh>& meshes, const std::vector<rtx::Matrix4>& models, unsigned int backgroundColor);
	void ClearBufferColor(unsigned int color = 0);
	void ClearBufferDepth(float depth = FLT_MAX);

private:
	void RenderMesh(Mesh mesh, const rtx::Matrix4& model);
	void RenderTriangle(VTriangle triangle, const rtx::Matrix4& model, unsigned int color);
};

