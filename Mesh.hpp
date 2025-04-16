#pragma once
#include <vector>
#include <cmath>
#include "VTriangle.hpp"
#include "Color.hpp"
#include "Vertex.hpp"

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

	static rtx::Vector3 CirclePoint(const float angle, const float radius, rtx::Vector3 center = rtx::Vector3::Zero());
};