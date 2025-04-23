#pragma once

#include "Buffer.hpp"
#include "RasTerX/include/Triangle.hpp"
#include "RasTerX/include/Matrix4.hpp"
#include "Mesh.hpp"
#include <memory>
#include "Light.hpp"

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

	void Render(std::vector<Mesh>& meshes, const std::vector<rtx::Matrix4>& models, const std::vector<std::shared_ptr<Light>>& lights, unsigned int backgroundColor);
	void ClearBufferColor(unsigned int color = 0);
	void ClearBufferDepth(float depth = FLT_MAX);

private:
	void RenderMesh(Mesh mesh, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights);
	void RenderTriangle(VTriangle triangle, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights, unsigned int color);

	void LightCalculation(Vertex& vert, const std::vector<std::shared_ptr<Light>>& lights);
};

