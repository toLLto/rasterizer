#pragma once

#include "Mesh.hpp"
#include "VTriangle.hpp"

class Cylinder : public Mesh
{
public:
	Cylinder(const float radius, const float height, const int radialSegments, const int heightSegments, const float distribution = 1.f);

	rtx::Vector2 TexCoords(float x, float y, float z, float height);
};