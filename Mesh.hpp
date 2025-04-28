#pragma once
#include <vector>
#include <cmath>
#include "VTriangle.hpp"
#include "Color.hpp"
#include "Vertex.hpp"
#include "RasTerX/include/Matrix4.hpp"

class Mesh
{
protected:
	std::vector<VTriangle> tris;
	std::vector<Vertex> verts;
	std::vector<rtx::Vector3> inds;

	std::vector<Color> colors;

public:
	Mesh() = default;
	virtual ~Mesh() = default;

	std::vector<VTriangle> GetTris();

	static rtx::Vector3 CirclePoint(const float angle, const float radius, rtx::Vector3 center = rtx::Vector3::Zero());
};

struct Renderable
{
	Mesh mesh;
	rtx::Matrix4 model;
	bool enableVertexLighting;

	Renderable(const Mesh& mesh, const rtx::Matrix4& model, bool enableVertexLighting = false)
		: mesh(mesh), model(model), enableVertexLighting(enableVertexLighting) {}
};