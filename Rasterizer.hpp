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

	void Render(std::vector<Renderable>& renderables, const std::vector<std::shared_ptr<Light>>& lights, unsigned int backgroundColor);
	void ClearBufferColor(unsigned int color = 0);
	void ClearBufferDepth(float depth = FLT_MAX);

private:
	void RenderMesh(Renderable renderable, const std::vector<std::shared_ptr<Light>>& lights);
	void RenderTriangle(VTriangle triangle, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights,
		unsigned int color, bool enableVertexLighting = true);

	void VertexLightCalculation(Vertex& vert, const rtx::Matrix4& model, const std::vector<std::shared_ptr<Light>>& lights);
	rtx::Vector3 PixelLightCalculation(const rtx::Vector3& position, const rtx::Vector3& normal, const rtx::Vector3& color, 
		const std::vector<std::shared_ptr<Light>>& lights);
};

